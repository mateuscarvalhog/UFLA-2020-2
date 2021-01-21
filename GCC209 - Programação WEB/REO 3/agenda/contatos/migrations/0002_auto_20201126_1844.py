# Generated by Django 3.1.3 on 2020-11-26 18:44

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('contatos', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Endereco',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('cep', models.CharField(max_length=9)),
                ('logradouro', models.CharField(max_length=100)),
                ('numero', models.CharField(max_length=10)),
                ('complemento', models.CharField(blank=True, max_length=100)),
                ('cidade', models.CharField(max_length=50)),
                ('estado', models.CharField(max_length=2)),
            ],
        ),
        migrations.AddField(
            model_name='pessoa',
            name='endereco',
            field=models.OneToOneField(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='contatos.endereco'),
        ),
    ]
