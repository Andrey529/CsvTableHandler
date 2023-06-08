# Сборка и запуск

## Сборка проектов

Стандартный способ сборки проекта утилитой cmake (старт из корня репозитория):
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Запуск проекта

В папке /build

```bash
./CsvHandler <input.csv>
```

## Запуск тестов

В папке /build/tests

```bash
./Google-Tests_run
```