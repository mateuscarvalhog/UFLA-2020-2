from django.test import TestCase
from django.test import Client
from django.contrib.staticfiles.testing import StaticLiveServerTestCase
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from .models import Pessoa
import time

class UnitTests(TestCase):
    def setUp(self):
        Pessoa.objects.create(nome="Vovó Juju", telefone="11 40028922", email="jujuzinha@jorel.com.br", anotacoes="", cep="35774-000", 
                              logradouro="Rua Poços de Caldas", numero="42", complemento="", bairro="Vizinhança", cidade="Jorelândia", estado="MG")

    def testeEmail(self):
        juju = Pessoa.objects.get(nome="Vovó Juju")
        self.assertEqual(juju.email, "jujuzinha@jorel.com.br")
        #self.assertEqual(juju.email, "juju@jorel.com.br")

class IntegrationTests(TestCase):
    def setUp(self):
        self.c = Client()
    
    def testeFuncionalCriar(self):
        print(self.c.get('/adicionarContato/'))
        
    def testeFuncionalEditar(self):
        print(self.c.get('/editarContato/1/'))

class SeleniumTests(StaticLiveServerTestCase):
    @classmethod
    def setUpClass(cls):
        super().setUpClass()
        cls.browser = webdriver.Chrome()
        cls.browser.implicitly_wait(10)
    
    @classmethod
    def tearDownClass(cls):
        cls.browser.quit()
        super().tearDownClass()
    
    def testSeleniumCriarContato(self):
        self.browser.get('http://127.0.0.1:8000/')
        self.browser.find_element_by_xpath('/html/body/div/button').click()
        
        nome = self.browser.find_element_by_xpath('/html/body/div/form/div[1]/input')
        nome.send_keys('Mateus Carvalho')
        
        telefone = self.browser.find_element_by_xpath('/html/body/div/form/div[2]/input')
        telefone.send_keys('91 992509119')
        
        cep = self.browser.find_element_by_xpath('/html/body/div/form/div[3]/input')
        cep.send_keys('37202853')
        
        numero = self.browser.find_element_by_xpath('/html/body/div/form/div[5]/input')
        numero.click()  # para api dos correios fazer autocomplete
        numero.send_keys('223')
        
        email = self.browser.find_element_by_xpath('/html/body/div/form/div[10]/input')
        email.send_keys('mateuscarvalho12@hotmail.com')
        
        time.sleep(3)
        self.browser.find_element_by_xpath('/html/body/div/form/div[12]/button[1]').click()        
