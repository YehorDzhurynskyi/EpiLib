@echo off

:main
  setlocal enabledelayedexpansion

  call :get-ini %1 env workdir workdir
  set workdir=%cd%\%workdir%

  call :get-ini %1 env epidir epidir
  set epidir=%cd%\%epidir%

  call :get-ini %1 cmake initial_cache initial_cache
  set initial_cache=%cd%\%initial_cache%

  call :get-ini %1 cmake generator generator

  call :get-ini %1 cmake arch arch

  call :get-ini %1 cmake toolchain toolchain

  set solution=%generator% %arch% %toolchain%
  set solution=%solution%
  set solution=!solution: =_!

  set cmake_extra_params=%2

  cmake -G "%generator%" -A "%arch%" -T "%toolchain%" -S "%workdir%" -B "%workdir%\_projects\%solution%" -DEPI_DIR="%epidir%" -C "%initial_cache%" %cmake_extra_params%

  goto :eof

:get-ini <filename> <section> <key> <result>
  set %~4=
  setlocal
  set insection=
  for /f "usebackq eol=; tokens=*" %%a in ("%~1") do (
    set line=%%a
    if "!line:~0,1!"=="[" (
      for /f "delims=[]" %%b in ("!line!") do (
        if /i "%%b"=="%2" (
          set insection=1
        ) else (
          endlocal
        )
      )
    )
    if defined insection (
      for /f "tokens=1,* delims==" %%b in ("!line!") do (
        if /i "%%b"=="%3" (
          endlocal
          set %~4=%%c
          goto :eof
        )
      )
    )
  )
  endlocal