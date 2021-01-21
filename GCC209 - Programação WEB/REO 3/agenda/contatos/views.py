from django.shortcuts import render, redirect
from .models import Pessoa
from .form import ContatoForm

def listaContatos(request):
    data = {}
    data['Pessoas'] = Pessoa.objects.all()

    return render(request, 'contatos/listaContatos.html', data)

def adicionarContato(request):
    data = {}
    form = ContatoForm(request.POST or None)
    data['form'] = form

    if form.is_valid():
        form.save()
        return redirect('listaContatos')

    return render(request, 'contatos/adicionarContato.html', data)

def editarContato(request, pk):
    pessoa = Pessoa.objects.get(pk=pk)
    data ={} 
    form = ContatoForm(request.POST or None, instance=pessoa)
    data['form'] = form
    data['pessoa'] = pessoa

    if form.is_valid():
        form.save()
        return redirect('listaContatos')

    return render(request, 'contatos/editarContato.html', data)

def excluirContato(request, pk):
    pessoa = Pessoa.objects.get(pk=pk)
    pessoa.delete()

    return redirect('listaContatos')

def mostrarEndereco(request, pk):
    pessoa = Pessoa.objects.get(pk=pk)
    data = {}
    data['pessoa'] = pessoa

    return render(request, 'contatos/mostrarEndereco.html', data)