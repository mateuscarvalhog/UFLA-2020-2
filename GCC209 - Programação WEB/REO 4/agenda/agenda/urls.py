"""agenda URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from contatos.views import listaContatos, adicionarContato, editarContato, excluirContato, mostrarEndereco

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', listaContatos, name='listaContatos'),
    path('adicionarContato/', adicionarContato, name='adicionarContato'),
    path('editarContato/<int:pk>/', editarContato, name='editarContato'),
    path('excluirContato/<int:pk>/', excluirContato, name='excluirContato'),
    path('mostrarEndereco/<int:pk>/', mostrarEndereco, name='mostrarEndereco'),
]
