REM --------- GO TO DEV FOLDER, CLEAN ALL, BUILD ALL

call cd ..\dev\
call CleanAll.Bat
call BuildAll.Bat
call cd ..\release\

REM Clean old folders

call rmdir /s/q .\File
call rmdir /s/q .\Math
call rmdir /s/q .\PCSTree
call rmdir /s/q .\Time

REM update Math libs

call mkdir .\Math\
call copy ..\dev\Math\Debug\*.lib .\Math\
call copy ..\dev\Math\Debug\*.pdb .\Math\
call copy ..\dev\Math\Release\*.lib .\Math\
call copy ..\dev\Math\Release\*.pdb .\Math\
call copy ..\dev\Math\MathEngine\*.h .\Math\

REM update File libs

call mkdir .\File\
call copy ..\dev\File\Debug\*.lib .\File\
call copy ..\dev\File\Debug\*.pdb .\File\
call copy ..\dev\File\Release\*.lib .\File\
call copy ..\dev\File\Release\*.pdb .\File\
call copy ..\dev\File\PA3\*.h .\File\

REM update PCSTree libs

call mkdir .\PCSTree\
call copy ..\dev\PCSTree\Debug\*.lib .\PCSTree\
call copy ..\dev\PCSTree\Debug\*.pdb .\PCSTree\
call copy ..\dev\PCSTree\Release\*.lib .\PCSTree\
call copy ..\dev\PCSTree\Release\*.pdb .\PCSTree\
call copy ..\dev\PCSTree\PA1\*.h .\PCSTree\

REM update Time libs

call mkdir .\Time\
call copy ..\dev\Time\Debug\*.lib .\Time\
call copy ..\dev\Time\Debug\*.pdb .\Time\
call copy ..\dev\Time\Release\*.lib .\Time\
call copy ..\dev\Time\Release\*.pdb .\Time\
call copy ..\dev\Time\*.h .\Time\

call cd ..\dev\
call CleanAll.Bat