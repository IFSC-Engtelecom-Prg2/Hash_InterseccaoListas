# Faz intersecção de duas listas

Uma necessidade recorrente é identificar valores que aparecem em dois conjuntos. Por exemplo, sabendo que usuários que acessam um sistema são registrados em um arquivo, poed-se querer saber que usuários acessaram o sistema em duas datas específicas. A generalização de uma solução pode ser feita por meio da intersecção de duas listas: o resultado seria uma nova lista contendo todos os valores que aparecem em ambas as listas. 

A função _interseccao_ implementa exatamente  isso:

```c++
template <type T> list<T> interseccao(const list<T> & l1, const list<T> & l2) {
  // aqui fica o corpo da função !
}
```

Note que essa função está definida como uma [função template](https://wiki.sj.ifsc.edu.br/index.php/Introdu%C3%A7%C3%A3o_C%2B%2B#Fun.C3.A7.C3.B5es_template).
Com isso, pode-se fazer a intersecção entre duas listas que armazenam qualquer tipo de dados.

Implemente a função _interseccao_ no arquivo _questao.h_. 