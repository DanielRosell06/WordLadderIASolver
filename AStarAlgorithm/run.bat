@echo off
chcp 65001 > nul

if not exist main_inadimissivel_log_test_01.exe (
    echo main_inadimissivel_log_test_01.exe nao encontrado.
    echo Compilando...

    gcc main.c node.c operations.c database.c -o main_log_XXX

    if errorlevel 1 (
        echo Erro na compilacao.
        pause
        exit /b 1
    )
)

main_inadimissivel_log_test_01.exe

pause