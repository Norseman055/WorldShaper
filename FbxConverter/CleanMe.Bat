rmdir /S /Q Debug
rmdir /S /Q ipch
rmdir /S /Q Release
del /F /S *.sdf
del /F /S /A:H *.suo

rmdir /S /Q FbxConverter\Debug
rmdir /S /Q FbxConverter\Release