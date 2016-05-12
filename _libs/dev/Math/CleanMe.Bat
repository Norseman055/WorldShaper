rmdir /S /Q Debug
rmdir /S /Q ipch
rmdir /S /Q Release
del /F /S *.sdf
REM del /F /S /A:H *.suo
rmdir /S /Q MathEngine\Debug
rmdir /S /Q MathEngine\Release
rmdir /S /Q MathEngineTest\Debug
rmdir /S /Q MathEngineTest\Release