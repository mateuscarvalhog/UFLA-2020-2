# Generated by Django 3.1.3 on 2020-11-20 13:42

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Pessoa',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('nome', models.CharField(max_length=100)),
                ('telefone', models.CharField(max_length=15)),
                ('email', models.EmailField(max_length=254)),
                ('anotacoes', models.TextField(blank=True, null=True)),
            ],
            options={
                'verbose_name_plural': 'Pessoas',
            },
        ),
    ]
