# Entendendo as estatísticas e saída do gem5.

Não podemos começar a usar um simulador sem entender a linguagem dele, não é mesmo? Assim como não faria sentido comprar um livro sem antes entender do que se trata ou sem saber do idioma em que ele foi escrito, não adianta fazermos simulações sem saber como ler os resultados. Para entender o simulador, temos 3 tipos de arquivos gerados no diretório `m5out`:
- **`config.ini`**: contém uma lista de todos os objetos que usamos na nossa simulação, além dos argumentos de seus parâmetros;
- **`config.json`**: mesma coisa do primeiro, só que no formato JSON;
- **`stats.txt`**: arquivo que contém todas as estatísticas do gem5 registradas para a simulação.

## O arquivo `config.ini`
Este arquivo registra todos os parâmetros, de cada SimObject, usados na simulação, sejam eles padrões ou definidos por usuário. Também mostra as estatísticas de cada objeto para que o usuário tenha ciência do que acabou de simular.

## O arquivo `stats.txt`
Nesse arquivo, cada instância de um SimObject tem suas próprias estatísticas. Pois bem, esse arquivo começa com a seção de descarregamento de estatísticas. Essa seção pode aparecer diversas vezes em um último arquivo, casa haja múltiplos descarregamentos durante a execução. 

### Uma pequena nota sobre o descarregamento de estatísticas
---

"Mas por quê essa seção apareceria tantas vezes?" Você se pergunta. A resposta é bem simples. Em simulações muito longas em que seja necessário o monitoramento de momentos específicos, ou mesmo etapas intermediárias em que é necessário o monitoramento dessas situações em específico, temos os chamados "checkpoints", que são pontos de retomada e que permitem pausar e continuar a simulação de um ponto previamente salvo. Os checkpoints são úteis para economizar tempo, especialmente em simulações complexas que levariam muito tempo para serem concluídas de uma só vez.

---

Após essas estatísticas serem emitidas, temos a exibição do estado atual das estatísitcas de todos os SimObjects. Boa parte das estatísticas é autoexplicativa. Algumas mais importantes são: 
- `sim_seconds` : tempo total simulado.
- `sim_insts`: número de instruções concluídos pela CPU.
- `host_inst_rate`: desempenho do gem5 em termos de instruções por segundo.
