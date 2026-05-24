# Laboratory work VIII

[![CI](https://github.com/georgij5920/lab08/actions/workflows/ci.yml/badge.svg)](https://github.com/georgij5920/lab08/actions/workflows/ci.yml)

Данная лабораторная работа посвящена изучению систем автоматизации развёртывания и управления приложениями на примере Docker.

## Что сделано

- Проект перенесен из `lab07` в `lab08`.
- Добавлен `Dockerfile` на базе `ubuntu:18.04`.
- В Docker-образ устанавливаются `gcc`, `g++`, `cmake`, `make`, `git` и `ca-certificates`.
- Исходный код копируется в контейнер, затем проект конфигурируется, собирается и устанавливается через CMake.
- Для приложения `demo` задана переменная окружения `LOG_PATH=/home/logs/log.txt`.
- Добавлен Docker volume `/home/logs`, чтобы файл лога сохранялся на хост-машине.
- Точкой входа контейнера является установленное приложение `demo`.
- Вместо TravisCI настроен GitHub Actions workflow, который собирает Docker-образ, запускает контейнер и проверяет содержимое `logs/log.txt`.

## Основные файлы

- `Dockerfile` — инструкция сборки Docker-образа `logger`.
- `.dockerignore` — исключения для Docker build context.
- `.github/workflows/ci.yml` — GitHub Actions workflow для проверки Docker-сборки.
- `demo/main.cpp` — приложение, читающее строки из `stdin` и записывающее результат в файл из `LOG_PATH`.
- `print_lib/` — библиотека для форматированной печати.

## Локальная сборка Docker-образа

```bash
docker build -t logger .
```

## Локальный запуск контейнера

```bash
mkdir -p logs
printf 'text1\ntext2\ntext3\n' | docker run --rm -i -v "$(pwd)/logs:/home/logs" logger
cat logs/log.txt
```

После запуска в файле `logs/log.txt` должны появиться строки, обработанные приложением `demo`.

## Обычная CMake-сборка без Docker

```bash
cmake -S . -B _build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
cmake --build _build
cmake --build _build --target install
LOG_PATH=logs/log.txt ./_install/bin/demo
```

## Описание workflow

Workflow выполняет три шага:

1. `docker build -t logger .` — сборка Docker-образа.
2. Запуск контейнера с примонтированной директорией `logs`.
3. Проверка, что `logs/log.txt` создан и содержит тестовые строки `text1`, `text2`, `text3`.
