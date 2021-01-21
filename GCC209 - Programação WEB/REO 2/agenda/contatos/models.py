from django.db import models

class Pessoa(models.Model):
    nome = models.CharField(max_length=100)
    telefone = models.CharField(max_length=15)
    email = models.EmailField(max_length=254)
    anotacoes = models.TextField(null=True, blank=True)

    class Meta:
        verbose_name_plural = 'Pessoas'

    def __str__(self):
        return self.nome
