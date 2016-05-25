rmdir /S /Q Debug
rmdir /S /Q ipch
rmdir /S /Q Release
del /F /S *.sdf
del /F /S *.idb
del /F /S /A:H *.suo

rmdir /S /Q UnitTests\Debug
rmdir /S /Q UnitTests\Release

rmdir /S /Q Application\Debug
rmdir /S /Q Application\Release

rmdir /S /Q WorldShaper\Debug
rmdir /S /Q WorldShaper\Release

rmdir /S /Q GLFWManager\Debug
rmdir /S /Q GLFWManager\Release

rmdir /S /Q CameraManager\Debug
rmdir /S /Q CameraManager\Release

rmdir /S /Q AnimationManager\Debug
rmdir /S /Q AnimationManager\Release

rmdir /S /Q GameObjectManager\Debug
rmdir /S /Q GameObjectManager\Release

rmdir /S /Q ModelManager\Debug
rmdir /S /Q ModelManager\Release

rmdir /S /Q ShaderManager\Debug
rmdir /S /Q ShaderManager\Release

rmdir /S /Q TextureManager\Debug
rmdir /S /Q TextureManager\Release

rmdir /S /Q ArchiveManager\Debug
rmdir /S /Q ArchiveManager\Release
