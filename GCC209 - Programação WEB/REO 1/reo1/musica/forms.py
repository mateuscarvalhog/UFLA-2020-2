from .models import Musica
from django import forms
from django.forms import ModelForm

class Cadastro_Musica(ModelForm):

    class Meta:
        model = Musica
        fields = '__all__'