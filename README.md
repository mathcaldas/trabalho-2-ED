# :briefcase: Trabalho 2 de Estrutura de Dados - Grupo P

### :gear: Como executar?
```shell
  git clone https://github.com/mathcaldas/trabalho-2-ED.git
  
  # Abra o diretório recém criado
  cd trabalho-2-ED
  
  # Execute o script usando make
  make
```
## Arquivos do Programa  

### Patients 

  * Funções para gerar CPF, Nome e Idade randomicamente 
  * Criação de uma lista encadeada para gerenciamento de clientes
  * Uso de variáveis estáticas para a criação de ID's únicas

### Exam e Report

  * Uso de uma estrutura de fila para simulação deste estudo de casos
  * Funções relacionadas ao controle dessa estrutura
    * como exemplos:
      * requeue;
      * dequeue;
        
##### No caso do report, existem funções para: 🤙

  * Gerenciamento de condições de pacientes
    * OBS: Consideramos HEALTHY como uma condição assim como as outras patologias, para o cálculo das métricas
  * Limpeza de dados após alcançar o limite definido
    

### Awaitable

  * Utilização de uma lista dinâmica de tamanho definido para seu uso:
    * Tamanho do Device (até 5 elementos) 
    * Tamanho do Radiologist (até 3 elementos)

### Utils

  * Função para gerar um inteiro aleatório num dado intervalo
    * Utilizado nas funçoes de gerar CPF, Nome e Idade
  * Função para retornar tempo de espera na fila para o laudo

##
