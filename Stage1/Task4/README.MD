Задача 4 на рекурсию. 

На каждом для всех соседних клеток с точкой пишем направление до текущей клетки и передаем рекурсию туда

4 вроде самый простой в реализации, просто понять нужно

Одна функция находит S

Вторая функция принимает массив массивов и текущую координату. 

Проверяет, можно ли пойти вверх (не вылез за стены); если встретил точку, пишешь в ней, что нужно пойти вниз, вызываешь эту же функцию из координаты сверху. 

Аналогично проверяешь слева (идти вправо), справа (идти влево), снизу (идти вверх). 

Если там уже нет клеток или уперся в стену, ничего не делаешь

Получишь ответ; ответ правильный, потому что по условию гарантируется единственность решения. 

Проверил, что можно идти в очередную сторону, проверил, что там точка, вызвал функцию из новой точки

(NOT DONE) (Done on java)