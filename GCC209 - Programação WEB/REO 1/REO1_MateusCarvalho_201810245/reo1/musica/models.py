from django.db import models
from datetime import datetime

# Create your models here.

class Musica(models.Model):
    
    nome = models.CharField(max_length=50, verbose_name="Nome")
    artista = models.CharField(max_length=50, verbose_name="Artista")
    album = models.CharField(max_length=50, verbose_name="Álbum")
    ano = models.IntegerField()

    class Meta:
        verbose_name = "Música"
        verbose_name_plural = "Músicas"
    
        def __str__(self):
            return self.nome