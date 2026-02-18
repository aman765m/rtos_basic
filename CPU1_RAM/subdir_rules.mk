################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-1100159638: ../c2000.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/aman-singh/ti/ccs2041/ccs/utils/sysconfig_1.26.0/sysconfig_cli.sh" -s "/home/aman-singh/ti/C2000Ware_6_00_01_00/.metadata/sdk.json" -d "F28002x" -p "64QFP" -r "F28002x_64QFP" --script "/home/aman-singh/workspace_ccstheia/rtos_basic/c2000.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1100159638 ../c2000.syscfg
syscfg/board.h: build-1100159638
syscfg/board.cmd.genlibs: build-1100159638
syscfg/board.opt: build-1100159638
syscfg/board.json: build-1100159638
syscfg/pinmux.csv: build-1100159638
syscfg/c2000ware_libraries.cmd.genlibs: build-1100159638
syscfg/c2000ware_libraries.opt: build-1100159638
syscfg/c2000ware_libraries.c: build-1100159638
syscfg/c2000ware_libraries.h: build-1100159638
syscfg/clocktree.h: build-1100159638
syscfg: build-1100159638

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/home/aman-singh/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="/home/aman-singh/workspace_ccstheia/rtos_basic" --include_path="/home/aman-singh/workspace_ccstheia/rtos_basic/device" --include_path="/home/aman-singh/ti/C2000Ware_6_00_01_00/driverlib/f28002x/driverlib/" --include_path="/home/aman-singh/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --define=DEBUG --define=RAM --define=__TMS320C28XX__ --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/home/aman-singh/workspace_ccstheia/rtos_basic/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/home/aman-singh/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="/home/aman-singh/workspace_ccstheia/rtos_basic" --include_path="/home/aman-singh/workspace_ccstheia/rtos_basic/device" --include_path="/home/aman-singh/ti/C2000Ware_6_00_01_00/driverlib/f28002x/driverlib/" --include_path="/home/aman-singh/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --define=DEBUG --define=RAM --define=__TMS320C28XX__ --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/home/aman-singh/workspace_ccstheia/rtos_basic/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


