# Criando um script simples

Aqui, faremos uma simples configuração de um script de simulação para o gem5. Lembrando que aqui faremos baseado no build do primeiro tutorial, com o `build/X86/gem5.opt`. Esse script modelará um sistema bem simples, com apenas:
- Um núcleo de CPU;
- barramentos;
- um canal de memória DDR3.

## Entendendo como funcionam os scripts de configuração do gem5:
O binário do gem5 tem como parâmetro um script em Python que configura e executa a simulação. Por ele é que somos capazes de criar o sistema que iremos simular, criar componentes e também determinar os parâmetros para os componentes que usaremos.

### Uma pequena nota sobre os SimObjects (objetos de simulação)
O design modular do gem5 gira em torno do tipo SimObject. A maior parte dos componentes que usamos para simulação são SimObjects: CPUs, caches, controladores de memória, barramentos, e outro. O gem5 exporta todos esses objetos de suas implementações em C++ para Python. Dentro dos scripts é que somos hábeis a criar os SimObjects, configurar seus parâmetros e especificar as interações entre eles.

## Criando um arquivo de configuração
Primeiramente, precisaremos criar uma nova pasta no diretório `configs` que temos dentro da pasta raiz do gem5. Dentro dela, faremos outra pasta chamada `part1` e criaremos um arquivo em Python chamado `simple.py`.
Dentro desse arquivo, vamos importar a biblioteca do m5 e os SimObjects que já temos:

``` python
import m5
form m5.objects import *
```

Lembre-se: dissemos que iríamos modelar um sistema simples que conteria um núcleo de CPU, barramentos e um canal de memória DDR3. Antes de qualquer código, temos que ter noção do que estamos fazendo antes de apenas "cuspir" letras ao léu. Para ter componentes de um sistema, precisamos, antes de um sistema para colocar os componentes. A partir disso podemos fazer todas as outras coisas. Para isso, instanciamos um objeto da classe `System`:

```python
system = System()
```

Agora, iremos definir o domínio de clock do sistema. Clock é nada mais nada menos que um sinal de temporização periódico que tem como finalidade sincronizar a operação de componentes do sistema. Isso permite que nosso simulador possa modelar corretamente o comportamento de temporização e consumo de energia com base nas características de clock e de tensão. Para tal, definimos:

```python
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()
```

O próximo passo é definir como a memória será simulada. Aqui, usaremos o modo de "timing" para a simulação e colocar um volume de 512 MB de tamanho de memória. Bem simples mesmo.

```python
system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]
```

Indo para o cérebro do nosso sistema, usaremos um CPU baseado no ISA do X86. O X86TimingSimpleCPU, o modelo que será usado, executa cada instrução em um único ciclo de clock de execução, exceto requisições de memória, que fluirão pelo sistema de memória. Simplesmente, instanciamos o objeto:

```python
system.cpu = X86TimingSimpleCPU()
```

Nesse momento, adicionaremos nosso último componente: o barramento. O barramento é definido da seguinte forma:

```python
system.membus = SystemXBar()
```

Agora que temos o barramento de memória, podemos conectar as portas de cache de nosso processador com ele. Como esse sistema não possui caches, não precisamos nos preocupar com outras coisas. Apenas em conectar as portas `I-cache` e `D-cache` diretamente no barramento.

```python
system.cpu.icache_port = system.membus.cpu_side_ports
system.cpu.dcache_port = system.membus.cpu_side_ports
```

### Uma pequena nota para o sistema de portas como abstração de conexões de componentes de memória 
---
De maneira resumida, ao invés de um sistema complexo de conexões de componentes de memória, o gem5 adota um esquema de portas. Tudo se baseia nas chamadas portas de requisição `(request ports)` e portas de resposta`(response ports)`. A porta de requisições manda as requisições (seja escrita, leitura) e a porta de resposta manda o resultado da requisição (um dado, ou permissão). A conexão dessas portas é feita por associação de uma porta de requisição com uma porta de resposta pelo símbolo de atribuição `=`. De certa forma, a associação com o símbolo de atribuição pode ser feito nos seguintes modelos:
- `porta_requisicao = porta_resposta`
- `porta_resposta = porta_requisicao`
Ou seja, não há bem uma hierarquia de atribuição. Os dois jeitos estão certos. Além disso, também podemos atribuir uma porta a um array de outras portas. Funciona da seguinte maneira: a parte que contém os arrays vai receber perceber a interação do outro tipo de porta e conectar diretamente a porta que corresponde à requisição, criando uma interação entre as duas. Ao final da operação, essa porta é liberada e a "`main port`" que faz a conexão entre a porta principal e esse "`hub`" de portas fica livre até a próxima requisição.

---

Estamos bem perto do fim. Antes, precisamos terminar mais algumas conexões para garantir que tudo funcione da maneira correta. Precisamos criar um controlador de entrada e saída, que chamamos de controlador de E/S na CPU e conectá-lo ao barramento de memória. Esse controlador é que gerencia a comunicação da CPU com dispositivos periféricos, gerenciando transferências de dados e interrupções para que haja uma interação eficiente entre dispositivos e memória do sistema. Além disso conectaremos uma porta especial no sistema ao barramento de memória. Essa porta é o que sistema precisa pra ler e escrever na memória. 

```python
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.mem_side_ports # Essas três linhas só são necessárias no x86
system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports
```

Por fim, colocaremos o controlador de memória e conectaremos ao barramento. Estaremos usando um controlador simples, o DDR3, que será responsável pelo volume de memória do nosso sistema.

```python
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports
```

Depois disso, instanciamos nosso sistema para simulação!

# TODO
- explicar o resto das coisas
