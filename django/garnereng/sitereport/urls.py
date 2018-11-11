from django.urls import path

from . import views

# URL paths:
urlpatterns = [
    path('', views.index, name='index'),
]
