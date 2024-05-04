# Бинарный поиск

## Задание

Вам необходимо написать программу для сортировки таблицы заданным методом
по вашему варианту и двоичного поиска по ключу в таблице.

Каждый элемент таблицы -- пара ключ (целое число) и текст записи (строка).

В программе должны быть реализованы сериализация и десериализация таблицы в/из **двоичного** файла.

Программа должна вводить значения элементов неупорядоченной таблицы и проверять
работу процедуры сортировки в трех случаях:

1. Элементы таблицы с самого начала упорядочены;
2. Элементы таблицы расставлены в обратном порядке;
3. Элементы таблицы не упорядоченны.

В последнем случае можно использовать встроенные процедуры генерации псевдослучайных
чисел.

В качестве текста для записей таблицы можно взять фрагменты прозы, ASCII-арт или
что-нибудь другое.

Программа должна иметь интерактивный командный интерфейс и реализовывать следующие команды:

- `create n` -- создать новую пустую таблицу в памяти из n записей;
- `save filename` -- сериализовать таблицу в файл с произвольным именем filename;
- `load filename` -- десериализовать таблицу из файла с произвольным именем filename;
- `search key` -- найти по ключу key значение;
- `sort` -- отсортировать таблицу по ключам;
- `shuffle` -- перемешать таблицу в случайном порядке;
- `quit` -- выйти из программы;
- `insert key value` -- вставить в пустой слот таблицы новую запись из ключа key и значения value;
- `replace index key value` -- заменить по индексу index запись с новым ключом key и значением value;
- `remove key` -- удалить запись с ключом key;
- `erase index` -- удалить запись с индексом index;
- `list` -- напечатать всю таблицу;
- `print index` -- напечатать только запись с индексом index;
- `help` -- показать справку;

Сама программа должна собираться с помощью утилиты `make` из рецептов в Makefile,
который предлагается реализовать самостоятельно.

Свой вариант можно найти в _таблице результатов_ во вкладке "Варианты".

### Уточнения по реализации

Таблица должна быть фиксированного размера, задаваемого командой `create`.
Ключи (целые числа) и значения (строки) храняться в **разных** массивах.

При попытке вставить `insert` в заполненную таблицу вывести сообщение "Table is full".

При попытке заменить `replace` или удалить `erase` запись с индексом, выходящим за пределы массива, вывести сообщение "Index out of range".

При попытке напечатать `print` запись с индексом, в котором ничего нет, напечатать "<Empty>".

При печати всей таблицы `list`, следует напечатать записи в формате "K: V", где K -- это ключ, а V -- это строка. Если в таблице записи нет, то печатать на её месте "<Empty>".

Если не удалось найти `find` значение по ключу, то вывести сообщение "Not found", иначе
напечатать строку в формате "K: V".

#### Протокол сериализации

Сеарилизированная таблица должна иметь следующий протокол:

Магия (первые четыре байта) в сериализуемом файле должны быть: `'V', 'S', 'D', 'B'`.
Далее должен идти байт, отражающий версию, он всегда должен быть со значением 1.

После этих метаданных идет 32-битное целое число N -- количество записей.
Далее идут N последовательных 32-битных чисел -- ключи таблицы.

После ключей идут последовательно строки. Каждая строка имеет 32-битное целое число --
длина строки. После этого числа идут последовательно символы строк в байтах.

При десериализации следует соблюсти следующие правила:

- При попытке прочитать таблицу из файла, не имеющую магию из байтов выше, вывести сообщение "Invalid table format" и прекратить чтение.
- Если версия оказалась не равна 1, то вывести сообщение "Unsupported table version" и
прекратить чтение;
- После успешного чтения вывести сообщение о количестве записей в таблице: "N table entries read".

## Варианты (сортировки)

1. Линейный выбор с обменом;
2. Метод пузырька;
3. Шейкер-сортировка;
4. Метод вставки;
5. Метод Шелла;
6. Турнирная сортирвка;
7. Пирамидальная сортировка с просеиванием;
8. Метод слияния;
9. Быстрая рекурсивная сортировка Хоара;
10. Быстрая нерекурсивная сортировка Хоара;

## Тестирование

Тестирование производится вручную. Все сериализованные таблицы складываются в
директорию `tests`.

В директории должны быть *хотя-бы* 3 файла, отражающие три случая выше в параграфе
"Задание".

Также приветствуется наличие файлов, которые не соответствуют протоколу сериализации.

## Важные требования к решению

Чтобы работа была засчитана, необходимо удовлетворять следующим критериям:
- Код должен быть понятным, названия переменных отражают то, что они хранят;
- Сериализиванные таблицы должны быть бинарными файлами и соответствовать протоколу,
описанному выше в параграфе "Уточнения по реализации";
- Ключи и значения должны быть физически в двух разных массивах;
- Должны быть реализованы все команды, приведенные выше.
- Программа должна собираться с помощью программы `make`;
- Запрещается использовать сторонние библиотеки, кроме стандартной;
