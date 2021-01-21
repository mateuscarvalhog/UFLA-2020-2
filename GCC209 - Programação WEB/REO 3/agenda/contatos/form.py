from django.forms import ModelForm
from .models import Pessoa

class ContatoForm(ModelForm):
    class Meta:
        model = Pessoa
        fields = '__all__'