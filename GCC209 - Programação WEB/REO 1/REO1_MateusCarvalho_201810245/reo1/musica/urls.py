from django.urls import path
from .views import Cadastro
from .views import Atualizar
from .views import Listar
from .views import Excluir

app_name = "musica"

urlpatterns = [
    path('cadastrar/musica', Cadastro, name='cadastrar_musica'),
    path('atualizar/<int:pk>', Atualizar, name='atualizar_musica'),
    path('listar/musica', Listar, name='listar_musica'),
    path('excluir/<int:pk>', Excluir, name='excluir_musica'),
]