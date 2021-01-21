from django.shortcuts import render, redirect
from .forms import Cadastro_Musica
from .models import Musica

# Create your views here.

def Cadastro(request):  
    data = {}

    form = Cadastro_Musica(request.POST or None)
    if form.is_valid():
        form.save()
        return redirect('Musica:listar_musica')

    data['form'] = form
    return render(request, 'musica/cadastro.html', data)

def Listar(request):
    data ={}
    data['Musicas'] = Musica.objects.all()

    return render(request, 'musica/listar.html', data)

def Atualizar(request, pk):
    data = {}
    
    musica = Musica.objects.get(pk=pk)
    form = Cadastro_Musica(request.POST or None, instance=musica)

    if form.is_valid():
        form.save()
        return redirect('Musica:listar_musica')
    
    data['form'] = form
    data['Musicas'] = musica

    return render(request, 'musica/atualizar.html', data)

def Excluir(request, pk):
    musica = Musica.objects.get(pk=pk)
    musica.delete() 

    return redirect('Musica:listar_musica')