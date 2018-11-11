# Generated by Django 2.1.3 on 2018-11-11 19:07

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('sitereport', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Client',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=254, verbose_name='company/client name')),
                ('address', models.CharField(max_length=254)),
                ('zip_code', models.CharField(max_length=10)),
            ],
        ),
        migrations.CreateModel(
            name='Person',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('first', models.CharField(max_length=128)),
                ('last', models.CharField(max_length=128)),
                ('email', models.EmailField(max_length=254)),
                ('phone', models.CharField(max_length=16)),
                ('company', models.ManyToManyField(to='sitereport.Client')),
            ],
        ),
        migrations.CreateModel(
            name='Project',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=254, verbose_name='project name')),
                ('client', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='sitereport.Client')),
            ],
        ),
        migrations.RemoveField(
            model_name='site',
            name='started',
        ),
        migrations.RemoveField(
            model_name='usstate',
            name='name',
        ),
        migrations.AddField(
            model_name='site',
            name='date_end',
            field=models.DateField(default=None, verbose_name='date ended'),
        ),
        migrations.AddField(
            model_name='site',
            name='date_start',
            field=models.DateField(default=None, verbose_name='date started'),
        ),
        migrations.AddField(
            model_name='site',
            name='zip_code',
            field=models.CharField(default=None, max_length=10),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='usstate',
            name='state',
            field=models.CharField(default=None, max_length=254),
            preserve_default=False,
        ),
        migrations.AlterField(
            model_name='site',
            name='street',
            field=models.CharField(max_length=254),
        ),
        migrations.AddField(
            model_name='client',
            name='state',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='sitereport.UsState'),
        ),
        migrations.AddField(
            model_name='site',
            name='project',
            field=models.ForeignKey(default=None, on_delete=django.db.models.deletion.CASCADE, to='sitereport.Project'),
        ),
    ]
