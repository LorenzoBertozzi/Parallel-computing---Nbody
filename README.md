<h1 align="center">Computação Paralela - Simulação de N-Corpos</h1>
<hr>

<p align="center" height=200px>
<img loading="lazy" src="http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge">
</p>

**Projeto semestral da disciplina de Computação Paralela — Engenharia de Computação**

Implementação e análise experimental do problema de **N-corpos**, com foco na aplicação de técnicas de **computação paralela em CPU e GPU**, utilizando **OpenMP** e **CUDA**.

O projeto busca investigar como diferentes estratégias de paralelização influenciam o desempenho de uma simulação de interações gravitacionais entre partículas, comparando diferentes configurações de execução e diferentes tamanhos de problema.

---

## Sobre o projeto

O problema de **N-corpos** consiste em simular a evolução de um conjunto de partículas submetidas à interação gravitacional entre si.

Na abordagem direta (*All-Pairs*), cada corpo precisa interagir com todos os demais, resultando em uma complexidade computacional de:

$$
O(N^2)
$$

Essa característica torna o problema um excelente estudo de caso para **computação paralela**, uma vez que uma grande quantidade de cálculos independentes pode ser distribuída entre diferentes unidades de processamento.

Neste projeto são investigadas principalmente duas estratégias:

* **OpenMP** — paralelização da execução em CPU utilizando múltiplas threads;
* **CUDA** — execução paralela em GPU utilizando milhares de threads.

Como extensão, também é considerada a possibilidade de investigar o algoritmo **Barnes-Hut**, que utiliza uma estrutura hierárquica espacial para reduzir o custo computacional aproximado para \(O(N\log N)\).

---

## Objetivos

### Objetivo geral

Desenvolver e avaliar uma implementação paralela de uma simulação de N-corpos, investigando o impacto da utilização de diferentes arquiteturas e modelos de programação paralela.

### Objetivos específicos

* Implementar a versão sequencial da simulação como referência;
* Implementar a paralelização utilizando **OpenMP**;
* Implementar, quando possível, uma versão utilizando **CUDA**;
* Comparar o tempo de execução das diferentes implementações;
* Avaliar o *speedup* obtido com a paralelização;
* Investigar a influência do número de corpos no desempenho;
* Analisar a escalabilidade da solução;
* Identificar as vantagens e limitações de CPU e GPU para esse tipo de problema.

---

## Fundamentação

O desenvolvimento do projeto está baseado em trabalhos clássicos e contemporâneos relacionados à simulação de N-corpos e computação de alto desempenho.

### Principais referências

| Ano      | Trabalho               | Contribuição                                                                        |
| -------- | ---------------------- | ----------------------------------------------------------------------------------- |
| **1986** | Barnes & Hut           | Algoritmo hierárquico Barnes-Hut e redução aproximada para \(O(N\log N)\)           |
| **1987** | Greengard & Rokhlin    | Fast Multipole Method (FMM), com complexidade \(O(N)\) sob as condições do método   |
| **2007** | Nyland, Harris & Prins | Implementação *All-Pairs* de N-corpos utilizando CUDA                               |
| **2011** | Burtscher & Pingali    | Implementação do Barnes-Hut inteiramente em CUDA                                    |
| **2012** | Dindar et al.          | Biblioteca Swarm-NG para integração paralela de múltiplos sistemas de poucos corpos |
| **2015** | Berczik et al.         | NBODY6++GPU, combinando MPI, OpenMP, CUDA e AVX                                     |
| **2019** | Gangavarapu et al.     | Estudo comparativo de implementações OpenMP e CUDA                                  |
| **2024** | Evangelista et al.     | Análise de arquiteturas paralelas aplicadas à simulação de N-corpos                 |

A seção de estado da arte e os trabalhos correlatos desenvolvidos durante a pesquisa estão documentados junto ao projeto.

---

## Abordagens avaliadas

### Implementação Sequencial

A implementação sequencial serve como **baseline** para as demais versões.

Cada corpo é comparado com os demais para determinar a força resultante e, posteriormente, atualizar sua velocidade e posição.

```text
Para cada corpo i:
    força_i = 0

    Para cada corpo j:
        calcular interação entre i e j

    atualizar velocidade de i
    atualizar posição de i
```

Complexidade:

$$
O(N^2)
$$

---

### OpenMP

A versão OpenMP explora o paralelismo disponível nos processadores multicore.

A ideia principal é distribuir entre diferentes threads os cálculos independentes das interações entre os corpos.

```text
CPU
 ├── Thread 1 → corpos
 ├── Thread 2 → corpos
 ├── Thread 3 → corpos
 └── Thread N → corpos
```

O desempenho é analisado em função de fatores como:

* número de threads;
* quantidade de corpos;
* tempo de execução;
* *speedup*;
* escalabilidade.

---

### CUDA

A implementação CUDA utiliza a GPU para explorar o elevado grau de paralelismo disponível no cálculo das interações.

```text
                 GPU
                  │
        ┌─────────┴─────────┐
        │                   │
     Bloco 0             Bloco 1
      │ │ │                │ │ │
      ▼ ▼ ▼                ▼ ▼ ▼
   Threads              Threads
```

A abordagem é particularmente interessante para o método *All-Pairs*, no qual milhares ou milhões de operações semelhantes podem ser executadas simultaneamente.

---

### Barnes-Hut

Como extensão, o projeto pode investigar o algoritmo **Barnes-Hut**.

Em vez de calcular explicitamente todas as interações, o espaço é subdividido em uma estrutura hierárquica.

```text
                Espaço
                   │
        ┌──────────┴──────────┐
        │                     │
     Região 1              Região 2
        │                     │
    ┌───┴───┐             ┌───┴───┐
    │       │             │       │
   ...     ...           ...     ...
```

A estratégia permite aproximar grupos de partículas distantes por meio de seu centro de massa, reduzindo significativamente o número de interações necessárias.

Complexidade aproximada:

$$
O(N\log N)
$$

---

## Avaliação de desempenho

Os experimentos procuram comparar as implementações utilizando diferentes tamanhos de entrada.

Entre as principais métricas analisadas estão:

### Tempo de execução

$$
T(N)
$$

Mede o tempo necessário para executar a simulação.

### Speedup

$$
S_p = \frac{T_1}{T_p}
$$

onde:

* \(T_1\) representa o tempo da execução de referência;
* \(T_p\) representa o tempo utilizando paralelismo.

### Eficiência

$$
E_p = \frac{S_p}{p}
$$

onde \(p\) representa o número de unidades de processamento utilizadas.

### Escalabilidade

Avaliação de como o desempenho varia conforme aumentam:

* o número de corpos;
* o número de threads;
* a quantidade de trabalho executada;
* os recursos computacionais disponíveis.

---

## Estrutura do projeto

A estrutura do repositório segue, inicialmente, a seguinte organização:

```text
.
├── README.md
├── docs/
│   ├── artigo/
│   ├── apresentacao/
│   └── referencias/
│
├── src/
│   ├── serial/
│   ├── openmp/
│   └── cuda/
│
├── benchmark/
│   ├── scripts/
│   └── resultados/
│
└── data/
    └── ...
```

> A estrutura poderá ser modificada conforme a evolução da implementação.

---

## Tecnologias

| Tecnologia     | Utilização                                  |
| -------------- | ------------------------------------------- |
| **C/C++**      | Desenvolvimento das implementações          |
| **OpenMP**     | Paralelização em CPU                        |
| **CUDA**       | Paralelização em GPU NVIDIA                 |
| **Git/GitHub** | Controle de versão e organização do projeto |
| **LaTeX**      | Desenvolvimento da documentação científica  |

---

## Requisitos

Para executar o projeto, recomenda-se um ambiente contendo:

* compilador C/C++;
* suporte a **OpenMP**;
* **NVIDIA CUDA Toolkit**, para a implementação em GPU;
* GPU NVIDIA compatível com CUDA, quando utilizada;
* ferramentas para compilação e execução dos experimentos.

A implementação sequencial e OpenMP pode ser executada sem uma GPU NVIDIA.

---

## Execução

### Versão sequencial

```bash
# Compilar
[comando de compilação]

# Executar
[comando de execução]
```

### Versão OpenMP

```bash
# Compilar com suporte a OpenMP
[comando de compilação]

# Executar
[comando de execução]
```

### Versão CUDA

```bash
# Compilar
[comando nvcc]

# Executar
[comando de execução]
```

> Os comandos acima serão atualizados conforme a estrutura final do projeto.

---

## Experimentos

Os experimentos serão realizados utilizando diferentes valores de \(N\), permitindo observar o comportamento das implementações conforme aumenta o número de corpos.

Exemplo de configuração experimental:

```text
N = 1.000
N = 5.000
N = 10.000
N = 25.000
N = 50.000
N = 100.000
...
```

Para cada configuração serão coletadas métricas de desempenho e, quando aplicável, comparadas as seguintes implementações:

```text
                 N-Corpos
                    │
          ┌─────────┼─────────┐
          │         │         │
       Serial    OpenMP     CUDA
          │         │         │
          └─────────┼─────────┘
                    │
             Comparação
                    │
       ┌────────────┼────────────┐
       │            │            │
      Tempo       Speedup    Escalabilidade
```

Os resultados serão apresentados por meio de tabelas e gráficos.

---

## Questão de investigação

O projeto busca responder, experimentalmente, questões como:

> **Qual é o impacto da paralelização utilizando OpenMP e CUDA no desempenho da simulação de N-corpos e como esse desempenho varia conforme o tamanho do problema?**

Também são investigadas questões relacionadas à escalabilidade e ao custo-benefício das diferentes arquiteturas.

---

## Referências principais

**BARNES, J.; HUT, P.** A hierarchical O(N log N) force-calculation algorithm. *Nature*, v. 324, p. 446–449, 1986.

**GREENGARD, L.; ROKHLIN, V.** A fast algorithm for particle simulations. *Journal of Computational Physics*, v. 73, n. 2, p. 325–348, 1987.

**NYLAND, L.; HARRIS, M.; PRINS, J.** Fast N-Body Simulation with CUDA. In: *GPU Gems 3*. Addison-Wesley, 2007.

**BURTSCHER, M.; PINGALI, K.** An Efficient CUDA Implementation of the Tree-Based Barnes Hut N-Body Algorithm. In: *GPU Computing Gems Emerald Edition*. Morgan Kaufmann, 2011.

**DINDAR, S. et al.** Swarm-NG: A CUDA Library for Parallel n-body Integrations. 2012.

**BERCIK, P. et al.** NBODY6++GPU: Ready for the gravitational million-body problem. *Monthly Notices of the Royal Astronomical Society*, v. 450, n. 4, p. 4070–4080, 2015.

**GANGAVARAPU, T. et al.** Parallel OpenMP and CUDA Implementations of the N-Body Problem. In: *Computational Science and Its Applications – ICCSA 2019*. Springer, 2019.

**EVANGELISTA, L. M. R. et al.** Arquiteturas Paralelas e a Simulação dos N-corpos: Uma Análise. In: *Anais da Escola Regional de Alto Desempenho do Rio de Janeiro – ERAD-RJ*, 2024.


## Autores

**Lorenzo Bertozzi e Daniel Mescolin**

Engenharia de Computação
CEFET-MG — Campus Leopoldina

