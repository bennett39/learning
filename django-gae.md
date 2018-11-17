# Deploying a Django Application to Google App Engine

Today, I successfully deployed a Django application that was working
locally to a Google App Engine instance online.

Google's docs and tutorials (https://cloud.google.com/python/django/appengine) 
for this process worked well, but they didn't do a good job of showing 
you what was going on under the hood with the sample application they 
had you deploy. When it came time to deploy an independent application, 
I hit a couple hurdles that I'll walk through in this post.

As with most of my blog posts, if you find this guide useful, awesome!
But I'm mostly writing it as a reference for my future self, because I
know I'll forget some of this stuff when I build another Django app and
want to deploy it.

## Prerequisites

You'll need the following to follow along with this guide:

- A Google Cloud Platform account
- A new project in your [Google Cloud dashboard](https://console.cloud.google.com/home/dashboard)
- Billing enabled for GCP account
- [Google Cloud SDK](https://cloud.google.com/sdk/install) installed
- [APIs enabled](https://console.cloud.google.com/flows/enableapi) for
  the project

## Structure

This post breaks down into the following sections in order to get an App
Engine instance running properly with a Django application. Each section
has a clear goal so you know when you're ready to move on to the next
step.

1. Make your app run locally
2. Change the SQL server to a Cloud SQL instance via a proxy
3. Modify settings.py to allow your app to connect to Cloud SQL
4. Add other necessary files/requirements to your Django app
5. Gather your staticfiles
6. Deploy and troubleshoot

## 1. Make your app run locally

I won't spend much time here, because this is basic Django stuff and
outside the scope of this guide. However, needless to say your app
should run locally on your computer.

It's usefull to think about how your app actually works before we start
trying to deploy it. In my case, my app has a Django webserver that
handles routing and rendering web pages. In addition, the Django server
connects to a SQL server in order to store model information in 
a database.

Since most apps have a database, most apps really need two servers to be
runnning simultaneously: the webserver and the SQL server. You'll
need to start the SQL server before the webserver so the webserver
has something to connect to when it starts up.

**Goal:** You can move on when you can type `python manage.py runserver`
and your application works locally at 127.0.0:8000 (or whatever port
you're using).

## 2. Change to a Cloud SQL server & run it locally via a proxy

Since the database comes first for any application, you'll need to
create your Google Cloud SQL instance before you can think about deploying
the app itself to Google's App Engine.

Visit your [Cloud SQL instances dashboard](https://console.cloud.google.com/sql/). 
Click "Create Instance" to start a new SQL instance. 

For the purposes of this guide, I used a MySQL 2nd Gen instance. I 
recommend it as it was fairly easy to set up.

Once the instance is created, you can get information about your
SQL server from the command line using the Google Cloud SDK (install it 
if you haven't already).

```bash
gcloud sql instances describe [YOUR_INSTANCE_NAME]
```
If this command runs successfully, it means you've done a few things
right. If it fails, one of these things could be the culprit:

- You installed and configured the Cloud SDK correctly
- You created a SQL instance in the current project and allowed it to
  fully initialize
- Your instance exists on Google's data platform and is connectable

Look toward the top of the output for a field called `connectionName`. 
Copy the connectionName as we'll need it to connect to the SQL instance
remotely.

Alternatively, you can also get the connectionName from your Instance
Details page in the GCP Console, under "Connect to this instance"

We've successfully created the SQL instance, but that doesn't mean we're
home free. We still need to connect to it from our local machine to
allow our app to run.

We need a server that can accept requests locally and relay them to our
new remote server. Luckily Google has already built such a tool, known
as Cloud SQL Proxy. To install it, navigate to the directory where your
Django app's `manage.py` is located. Then run the following command to
download the proxy:

```bash
wget https://dl.google.com/cloudsql/cloud_sql_proxy.linux.amd64 -O
cloud_sql_proxy
```

You'll need to change that downloaded file's permissions in order for
your machine to execute it:

```bash
chmod +x cloud_sql_proxy
```

Now we're ready to do some linkage between our local machine and the
Cloud SQL instance we just created. This will start the SQL server
for our local development purposes and our Django app will be able to
connect to the SQL server (once we change the app's settings).

To start the SQL server locally:

```bash
./cloud_sql_proxy -instances="[YOUR_INSTANCE_CONNECTION_NAME]"=tcp:3306
```

Replace [YOUR_INSTANCE_CONNECTION_NAME] with the `connectionName` that
we copied above.

**Goal:** If you're successful, you should see:

```
2018/11/16 13:52:35 Listening on 127.0.0.1:3306 for [connectionName]
2018/11/16 13:52:35 Ready for new connections
```

**One more step:** Now that your SQL instance is working, you'll need to
create a user to connect to that SQL instance and a database inside that
instance. This is fairly easy inside the Google Cloud Dashboard -
https://console.cloud.google.com/sql/instances/ .

Create both a new user and a new database.

## 3. Modify settings.py so Django can talk to the new database

Leave the database server (Cloud SQL Proxy) running in the background.
It needs to be listening for requests, because we're about to connect to
it!

Open `settings.py` in your Django project. We need to update the
database settings so they'll point to Google Cloud SQL instead of
whatever local database you were using.

Typically, we specify only one database within `settings.py`. But in
this case, we're going to use an if/else statement to let the
application determine if it's being run locally in development or on the
actual web server in staging/production.

This will be useful when we actually deploy the application. In
production, the application will connect directly to Cloud SQL via a
URL. In development on our local machine, it will know to use the Cloud
SQL Proxy that we just installed and are running in the background.

To set up this if/else statement, replace your current database config
information with this in `settings.py`:

```python
# [START db_setup]
if os.getenv('GAE_APPLICATION', None):
    # Running on production App Engine, so connect to Google Cloud SQL using
    # the unix socket at /cloudsql/<your-cloudsql-connection string>
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.mysql',
            'HOST': '/cloudsql/[YOUR-CONNECTION-NAME]',
            'USER': '[YOUR-USERNAME]',
            'PASSWORD': '[YOUR-PASSWORD]',
            'NAME': '[YOUR-DATABASE]',
        }
    }

else:
    # Running locally so connect to either a local MySQL instance or connect 
    # to Cloud SQL via the proxy.  To start the proxy via command line: 
    #    $ cloud_sql_proxy -instances=[INSTANCE_CONNECTION_NAME]=tcp:3306 
    # See https://cloud.google.com/sql/docs/mysql-connect-proxy
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.mysql',
            'HOST': '127.0.0.1',
            'PORT': '3306',
            'NAME': '[YOUR-DATABASE]',
            'USER': '[YOUR-USERNAME]',
            'PASSWORD': '[YOUR-PASSWORD]',
        }
    }
# [END db_setup]
```

Use `connectionName` and the username, password, and database names you
created in the previous step. 

Notice that the `else` statement specifies a port for the SQL server of 
3306 when you're running locally. When you intialize the proxy server, 
make sure to include the `=tcp:3306` at the end of the command.
Otherwise, Django will never find the server and you'll get a timeout
error.

**Goal:** If you've updated `settings.py` correctly, you should be able
to run your app locally.

Before you try it, though, keep in mind that you're using a fresh new
database. It doesn't have any information about the tables/models it
needs to contain. So, we need to `makemigrations` first.

```bash
python manage.py makemigrations
```

You might see that Django doesn't think there are new migrations.
Especially if you've been developing this app locally already for a
while.

To get Django to `makemigrations` from scratch you'll need to move or
remove all the existing migrations from the `migrations` folder in your
app.

Once you've got Django making migrations from scratch use the `python
manage.py migrate` command to apply those migrations to your Cloud SQL
database. This is the first test of your database setup, so cross your
fingers it works!

If successful, you should be able to run `python manage.py runserver` 
and your app will deploy locally, but using the Cloud SQL server as the
database.

**Bonus Step:** You can go ahead and create a Django admin superuser
now. Just type `python manage.py createsuperuser`

## 4. Add other necessary files/requirements to your app

At this point, your app works using a Google Cloud SQL backend. Now, you
just need to be able to deploy the Django app itself to the Google App
Engine.

However, this is the point where Google's Django deployment tutorial
ends. It just says to type `$ gcloud app deploy` and voila, everything
should work!

Of course, that works with Google's carefully prepared tutorial
repository and app, but it leaves out a lot of stuff you need to do to
get an existing Django app ready for deployment on App Engine.

I'll create subjeadings for each file you'll need to create/update in
your app for it to work on App Engine. All of these edits are necessary.

I'll use the directory names `/`, `/mysite`, and `/myapp` to specify
which folder all these files go in in your Django project. Obviously,
use whatever naming scheme your Django app uses.

### `/app.yaml`

This is the basic config file for App Engine. You can change a lot of
settings here, but the most basic configuration will get your app up and
running for now. Just use this:

```python

# [START django_app]
runtime: python37

handlers:
# This configures Google App Engine to serve the files in the app's
# static directory.
- url: /static
  static_dir: static/

# This handler routes all requests not caught above to the main app. 
# It is required when static routes are defined, but can be omitted 
# (along with the entire handlers section) when there are no static 
# files defined.
- url: /.*
  script: auto

# [END django_app]
```

### `/main.py`

This is just a file App Engine looks for by default. In it, we just
import a single variable from elsewhere in our Django project
(/mysite/wsgi.py)

```python
from mysite.wsgi import application

# App Engine by default looks for a main.py file at the root of the app
# directory with a WSGI-compatible object called app.
# This file imports the WSGI-compatible object of the Django app,
# application from mysite/wsgi.py and renames it app so it is
# discoverable by App Engine without additional configuration.
# Alternatively, you can add a custom entrypoint field in your app.yaml:
# entrypoint: gunicorn -b :$PORT mysite.wsgi
app = application
```

### `/requirements.txt`

App Engine needs to know what dependencies to install in order to get
your app running. If you've got your app running locally with no
problems (In an IDE or on Ubuntu), you can use pip to freeze your 
dependencies. Ideally, you used a virtual environment to separate your 
app's dependencies from the rest of your machine's installations. If 
not, that's something to read up on and implement, but it's way outside 
the scope of this post.

Freeze your dependencies like so:

```bash
$ touch requirements.txt
$ pip freeze >> requirements.txt
```

### `/mysite/settings.py`

We already changed the database settings in `settings.py` but we need to
add one more thing. A `STATIC_ROOT` to tell the App Engine where to look
for CSS, Javascript, Images, etc.

The `STATIC_URL` field should already be in your `settings.py`, but if
it's not or if it's not configured as below, update it.

```python
# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/2.1/howto/static-files/

# Google App Engine: set static root for local static files
# https://cloud.google.com/appengine/docs/flexible/python/serving-static-files
STATIC_URL = '/static/'
STATIC_ROOT = 'static'
```

### `/mysite/wsgi.py`

This file should already exist and be correctly implemented. But if
you've made changes to it, or if there are problems, here is what it
should look like. Take care to change all references to `mysite` to
whatever your Django app's naming scheme is.

```python
"""
WSGI config for mysite project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/2.1/howto/deployment/wsgi/
"""

import os

from django.core.wsgi import get_wsgi_application

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'mysite.settings')

application = get_wsgi_application()
```

## 5. Gather Static Files

The final step before you deploy your app is to gather all your app's
static content in a single folder that the App Engine knows it won't
have to update and can always access.

Django does this for you pretty easily:

```bash
python manage.py collectstatic
```

### 6. Deploy your app

Hopefully after you've frozen the requirements, added necessary files,
and collected static, your app should be ready for deployment. So try:

```bash
glcoud app deploy
```

If you get a success message, congratulations! If you get a traceback,
see what the error is and try to debug. Google is your friend here.

A success message alone isn't enough though - actually load your
application via the URL that `gcloud app deploy` provides. For instance,
I got a 502 Bad Gateway error, even though my app "successfully"
deployed.

In my case, the problem was with my `settings.py` configuration. If you
have remaining errors, you'll have to Google them, but this guide should
have gotten you pretty close to a fully working Django app on Google's
App Engine.

## Conclusion

I'm excited to learn more about Google Cloud and gain experience using
web service providers. I've deployed to Heroku before, but I was much
less happy with the result than I am with my first deployment on Google
Cloud. I'm considering moving several applications over to GCP now that
I know the basics of how to use it.
