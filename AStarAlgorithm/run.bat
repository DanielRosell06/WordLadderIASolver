@echo off
chcp 65001 > nul

if not exist main_log.exe (
    echo main_log.exe nao encontrado.
    echo Compilando...

    gcc main.c node.c operations.c database.c -o main_log

    if errorlevel 1 (
        echo Erro na compilacao.
        pause
        exit /b 1
    )
)

main_log.exe

pause