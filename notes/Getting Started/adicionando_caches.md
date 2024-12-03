# Adicionando caches ao nosso projeto
---

### Antes de tudo, entendendo os tipos de cache que poderemos usar no gem5.
- Caches clássicas: implementam um modelo flexível e simples com protocolo de coerência MOESI;
- Ruby: implementam um modelo mais robusto, modelando a coerência de maneira mais completa que a clássica. podendo até definir protocolos personalizados de coerência.

O uso de um dos dois depende da especificação do projeto.


## A cache
A memória cache do gem5 se encontra em `src/mem/cache/Cache.py`. Essa classe é uma classe filha de classe `BaseCache`. Essa última classe por sua vez, tem alguns parâmetros como `assoc`, `tag_latency`, `mshrs` e outros. Porém alguns ajustáveis e que vão nos ajudar a criar nossas memórias cache para o sistema são:
- assoc (associatividade)
- size (tamanho do cache)
- tag_latency (latência de busca de tag)
- data_latency (latência de dados)
- mshrs (número de entradas de miss status holding registers)

Após definir alguns parâmetros para as memórias, tambémm as conectaremos com seus respectivos componentes.
