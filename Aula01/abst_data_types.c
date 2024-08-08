/* TIPOS ABSTRATOS DE DADOS (TAD)

Tipo de Dado -> "método para interpretar o conteúdo da memória do computador; define quantos bytes devem ser alocados para representar aquele valor e como interpretar seus bits"

Estrutura de Dados -> "organização de dados e operações (algoritmos) com esses dados que facilitam a solução de um problema"

Tipos Básicos (Simples) -> padrões, já vem com a linguagem
Tipos Abstratos (Estruturados) -> implementados pelo usuário, compostos de tipos simples usando structs
    -> divididos em 2 MÓDULOS
        -> INTERFACE: prototipagem (declaração) das funções/operações que involvem aquele tipo
            -> biblioteca .h
            -> não contém os detalhes de implementação
            -> podemos alterar detalhes da implementação, mas NÃO podemos mudar a interface, pois isso forçaria o cliente a mudar seu código
        -> IMPLEMENTAÇÃO/DEFINIÇÃO: implementação das funções do TAD e definição dos tipos de dados
            -> arquivo(s) .c
    -> conjunto de valores e uma sequência de operações sobre esses valores
        -> ENCAPSULAMENTO (organização) de dados
            -> uso da interface sem necessidade de saber da implementação (OCULTAMENTO DE INFORMAÇÃO)
                -> só se tem acesso às operações de manipulação de dados, não aos dados em si
                    -> por causa disso, a definição da struct tem que estar dentro do .c, e apenas seu protótipo deve estar na .h
                -> evita problemas como aquele da Crowdstrike (2024)
            -> eficiência de tempo e espaço são preocupações para o desenvolvedor do TAD, não do usuário/cliente
    -> vantagens:
        1. reuso
        2. manutenção/correção/evolução
        3. independência da representação de dados (desde que a interface não seja alterada)
    -> OBS 1: sem encapsulamento e ocultamento de informação, não é um TAD!!!
    -> OBS 2: em C, todo TAD é um ponteiro!!!
        -> se houver um dado novo, o compilador precisa saber o nome da struct e seu tamanho em bytes
        -> prototipando uma struct no arquivo .h, não informamos o tamanho dela, mas por ser um ponteiro (na main), o compilador já sabe o tamanho do dado (ponteiro sempre tem 8 bytes)
            -> se não fosse um ponteiro, teríamos que informar o tamanho da struct de algum outro jeito
        -> em outras linguagens não precisa ser um ponteiro, só precisamos definir os dois módulos
*/