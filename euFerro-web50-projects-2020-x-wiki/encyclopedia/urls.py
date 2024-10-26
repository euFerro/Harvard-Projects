from django.urls import path

from . import views

app_name = "wiki"
urlpatterns = [
    path("", views.index, name="index"),
    path("wiki/<str:title>", views.page, name="page"),
    path("search", views.search, name="search"),
    path("newpage", views.newpage, name="newpage"),
    path("editpage", views.editpage, name="editpage"),
    path("randompage", views.randompage, name="randompage")
]
