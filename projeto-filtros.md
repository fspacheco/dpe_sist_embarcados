# Processo de desenvolvimento de aplicações de processamento digital de sinais

Neste tópico, o objetivo é apresentar o processo de desenvolvimento de aplicações de processamento digital de sinais. Para tanto, iremos explorar uma aplicação específica: redução de ruído em áudio.

Então, faremos o projeto e implementação de um filtro digital.

O processo consiste em:
1. Definição dos requisitos
2. Definição das especificações de projeto filtro
3. Projeto e avaliação usando ferramenta computacional
4. Implementação em hardware específico
5. Avaliação e testes

## Definição dos requisitos
Nesta etapa, é importante conhecer o problema e levantar características do sinal de interesse e daquele indesejado (ruído). É importante preservar a fase do sinal? Qual a relação sinal/ruído? Em que plataforma será implementado? Qual a demanda de processamento (um ou mais canais; taxa de amostragem)?

## Definição das especificações de projeto filtro
De posse dos requisitos, podemos iniciar a especificação do filtro. Aqui é importante definir: tipo de filtro (FIR ou IIR), método de projeto, ordem do filtro, resposta em frequência (magnitude e fase).

## Projeto e avaliação usando ferramenta computacional
Várias ferramentas podem ser usadas para o projeto. Dentre várias, podemos citar:
- Matlab/Octave
- Python/Scipy
- Ferramentas específicas de fabricantes (Xilinx, Texas)
- Micromodeler (online)
Espera-se que a ferramenta forneça alguma forma de visualização gráfica.

## Implementação em hardware específico
Nessa etapa, é importante rever os requisitos e o projeto da etapa anterior para das características do hardware assim como do firmware. Algumas perguntas relevantes:
- O hardware opera em ponto fixo ou flutuante?
- Qual a taxa de amostragem suportada?
- Em que linguagem será implementado o algoritmo?
- Há bibliotecas do fabricante ou de terceiros que possam ser usadas para acelerar o desenvolvimento?
- Qual o grau de suporte do fabricante? 

## Avaliação e testes
Nesta etapa, verificamos se os requisitos iniciais foram atendidos. É comum usar sinais de teste padronizados como tons, sinais de varredura (sweep), ruído rosa (para áudio) além de sinais de voz e música.

Referências
Agilent: Designing a Digital Filter. Disponível em:
http://literature.cdn.keysight.com/litweb/pdf/ads2008/dfilter/ads2008/Designing_a_Digital_Filter.html

Mauer, V. Altera: Designing Filters for HighPerformance. Disponível em: https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/wp/wp-01260-stratix10-designing-filters-for-high-performance.pdf

Matlab: Practical Introduction to Digital Filter Design. Disponível em: https://www.mathworks.com/help/signal/ug/practical-introduction-to-digital-filter-design.html

Digital Filters. Disponível em http://www.analog.com/media/en/training-seminars/design-handbooks/MixedSignal_Sect6.pdf

The free online FIR filter design tool. Disponível em http://t-filter.engineerjs.com/
