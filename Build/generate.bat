@echo off

:main
  setlocal enabledelayedexpansion

  call :get-ini %1 env workdir workdir
  set workdir=%cd%\%workdir%

  call :get-ini %1 env epibuilddir epibuilddir
  set epibuilddir=%cd%\%epibuilddir%

  call :get-ini %1 cmake initial_cache initial_cache
  set initial_cache=%cd%\%initial_cache%

  call :get-ini %1 cmake generator generator

  call :get-ini %1 cmake arch arch

  call :get-ini %1 thirdparty qtdir qtdir

  cmake -G "%generator%" -A "%arch%" -S "%workdir%" -B "%workdir%\_projects\%generator% %arch%" -DEPI_BUILD_DIR="%epibuilddir%" -DQt5_DIR="%qtdir%" -C "%initial_cache%"

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