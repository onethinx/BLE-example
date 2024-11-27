project('meson_test', 'c',
	version : '0.1',
	default_options : ['warning_level=3']
)

[host_machine]
system     = 'none'
cpu_family = 'arm'
cpu        = 'cortex-m3'
endian     = 'little'

#================================================================================================================================#
# check Creator_PostBuild version and set various variables for possible use

# Creator_PostBuild_Minumum_Version: '2.13' - used for checking Creator_PostBuild minimum version, do not remove

# Creator_PostBuild_Version_Line - automatic insert of Creator_PostBuild version. Do not edit the line below
creatorPostBuildVersion = '2.20'

# Creator_PostBuild_DateTime_Line - automatic insert of Creator Generated DateTime. Do not edit the line below
creatorGeneratedDateTime = '2024-08-08 13:57:49'

# Creator_PostBuild_devicePart_Line - automatic insert of device part by Creator_PostBuild. Do not edit the line below
devicePart = 'CY8C5888AXI-LP096'

# Creator_PostBuild_linkerFile_Line - automatic insert of linker file by Creator_PostBuild. Do not edit the line below
linkerFile = './Generated_Source/PSoC5/cm3gcc.ld'

# Creator_PostBuild_SVDfile_Line - automatic insert of SVD file by Creator_PostBuild. Do not edit the line below
SVDfile = 'PSoC_Creator.svd'

# Creator_PostBuild_prePostBuild_Lines - automatic insert of pre- and postbuild commands by Creator_PostBuild. Do not edit the two line below
preBuildCommands = ''
postBuildCommands = ''

# set directories
# Creator_PostBuild_Directory_Line - automatic insert of Creator Project main directory. Do not edit the line below
creatorDirectory = 'PSoC_Creator.cydsn'

# OTX_Extension_print(PROJECTNAME = '${workspaceFolderBasename}')
PROJECTNAME = 'PSoC5_VS_Code'

# OTX_Extension_print(ONETHINX_PACK_LOC = '${env:ONETHINX_PACK_LOC}')
ONETHINX_PACK_LOC = '/Applications/OTX-Maestro'

CONFIG_DIR 			= ONETHINX_PACK_LOC + '/config'
GCC_DIR 			= ONETHINX_PACK_LOC + '/gcc-arm/bin'
BIN_DIR 			= ONETHINX_PACK_LOC + '/bin'
SCRIPTS_DIR 		= ONETHINX_PACK_LOC + '/config/scripts'

MESON_SOURCE_LOC 	= meson.current_source_dir()
CREATOR_DIR 		= MESON_SOURCE_LOC + '/' + creatorDirectory

#================================================================================================================================#
# import tools

objcopy  		= find_program(GCC_DIR + '/arm-none-eabi-objcopy').path()
objdump  		= find_program(GCC_DIR + '/arm-none-eabi-objdump').path()
size     		= find_program(GCC_DIR + '/arm-none-eabi-size').path()
gdb      		= find_program(GCC_DIR + '/arm-none-eabi-gdb').path()
cymcuelftool 	= find_program(BIN_DIR + '/cymcuelftool').path()
readelf  		= find_program(GCC_DIR + '/arm-none-eabi-readelf').path()
memcalc 		= find_program(BIN_DIR + '/memcalc').path()
cyelftool       = find_program(BIN_DIR + '/cyelftool').path()

#================================================================================================================================#
# setup compile & link arguments

assembler_args = [
# Creator_PostBuild_AssemblerOptions_Start - automatic insert of assembler options by Creator_PostBuild. Do not edit below this line
	'-mcpu=cortex-m3',
	'-mthumb',
	'-g',
	'-W',
# Creator_PostBuild_AssemblerOptions_End - automatic insert of assembler options by Creator_PostBuild. Do not edit above this line
]

compiler_args     = [
# Creator_PostBuild_CompilerOptions_Start - automatic insert of compiler options by Creator_PostBuild. Do not edit below this line
	'-mcpu=cortex-m3',
	'-mthumb',
	'-g',
	'-DDEBUG',
	'-DCY_CORE_ID=0',
	'-Wall',
	'-ffunction-sections',
	'-ffat-lto-objects',
	'-Og',
# Creator_PostBuild_CompilerOptions_End - automatic insert of compiler options by Creator_PostBuild. Do not edit above this line
]

linker_args     = [
# Creator_PostBuild_LinkerOptions_Start - automatic insert of linker options by Creator_PostBuild. Do not edit below this line
	'-mcpu=cortex-m3',
	'-mthumb',
	'-L'+CREATOR_DIR+'/Generated_Source/PSoC5',
	'-T'+CREATOR_DIR+'/Generated_Source/PSoC5/cm3gcc.ld',
	'-specs=nano.specs',
	'-Wl,--gc-sections',
	'-g',
	'-ffunction-sections',
	'-Og',
	'-ffat-lto-objects',
# Creator_PostBuild_LinkerOptions_End - automatic insert of linker options by Creator_PostBuild. Do not edit above this line
]

include_dirs       = [
# OTX_Extension_HeaderFiles_Start - automatic insert of source files by the OTX VSCode extension. Do not edit below this line
# OTX_Extension_HeaderFiles_End - automatic insert of source files by the OTX VSCode extension. Do not edit above this line

# Creator_PostBuild_IncludeFolders_Start - automatic insert of include header folders by Creator_PostBuild. Do not edit below this line
	'PSoC_Creator.cydsn/',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5',
# Creator_PostBuild_IncludeFolders_End - automatic insert of include header folders by Creator_PostBuild. Do not edit above this line
]

sourcefiles       = [
# manual insert of Creator_PostBuild stripped files

# OTX_Extension_SourceFiles_Start - automatic insert of source files by the OTX VSCode extension. Do not edit below this line
	'source/main.c',
# OTX_Extension_SourceFiles_End - automatic insert of source files by the OTX VSCode extension. Do not edit above this line

# Creator_PostBuild_SourceFiles_Start - automatic insert of source files by Creator_PostBuild. Do not edit below this line
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/cyfitter_cfg.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/cymetadata.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/Cm3Start.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/CyDmac.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/CyFlash.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/CyLib.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/cyPm.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/CySpc.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/cyutils.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/cy_em_eeprom.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_0.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_1.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_2.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_3.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_4.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_5.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_6.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P2_7.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/Timer_1.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/Timer_1_PM.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/Clock_1.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/P0_7.c',
	'PSoC_Creator.cydsn/Generated_Source/PSoC5/CyBootAsmGnu.s',
# Creator_PostBuild_SourceFiles_End - automatic insert of source files by Creator_PostBuild. Do not edit above this line
]

#================================================================================================================================#
# include libraries

cc = meson.get_compiler('c')

# example: include library.a from directory
#link_deps = declare_dependency( dependencies : cc.find_library('library', dirs : ['directory/libdir']) )

link_deps = [
# Creator_PostBuild_LibSources_Start - automatic insert of include source files by Creator_PostBuild. Do not edit below this line
	declare_dependency( dependencies : cc.find_library('CyComponentLibrary', dirs : [CREATOR_DIR + '/./Export/ARM_GCC_Generic']) ),
# Creator_PostBuild_LibSources_End - automatic insert of include source files by Creator_PostBuild. Do not edit above this line
]


#================================================================================================================================#
# run prebuild script 

#prebuild = custom_target('prebuild', output : 'buildversion.h', command : [MESON_SOURCE_LOC+'/config/prebuild.bash'])
#link_deps += declare_dependency( sources : [prebuild])

#================================================================================================================================#
# build executable

main = executable(
            PROJECTNAME,          [sourcefiles],
            name_suffix         : 'elf',
            c_args              : [compiler_args],
            link_args           : [linker_args],
            dependencies        : link_deps,
            include_directories : [include_dirs] )

#================================================================================================================================#
# create custom target : create binary, hex dump, size and disassemble dump

elfout = custom_target(
                        PROJECTNAME + '.elf',
    output           : [PROJECTNAME + '1.elf'],
    build_by_default : true,
    command          : [cyelftool, '-C',  PROJECTNAME + '.elf', '--flash_row_size', '256', '--flash_size', '262144', '--flash_offset', '0x00000000'],
    depends          : [main])

noeepromout = custom_target(
                        PROJECTNAME + '_no_eeprom.elf',
    output           : [PROJECTNAME + '_no_eeprom.elf'],
    build_by_default : true,
    command          : [objcopy, '-R',  '.cyeeprom', PROJECTNAME + '.elf', PROJECTNAME + '_no_eeprom.elf'],
    depends          : [main, elfout])

#COMMAND "${OBJCOPY_TOOL}" -R .cyeeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}_no_eeprom.elf >/dev/null 2>&1
mainout = custom_target(
                        PROJECTNAME + '.memcalc.txt',
    output           :  [PROJECTNAME + '.memcalc.txt'],
    build_by_default : true,
	console			 : true,
    command          : [memcalc, readelf, PROJECTNAME + '.elf', '0x40000', '0x10000', '0x00000000', '0x1FFF8000', PROJECTNAME + '.memcalc.txt'],  #Flash 0x0e0000   SRAM 0x38000   Flash start 0x10000000   SRAM start 0x08000000
    depends          : [main, noeepromout])

# create custom target : create binary, hex dump, size and disassemble dump
# mainbin = custom_target(
#                         'main.bin',
#     output           : ['main.bin'],
#     # name_suffix      : 'bin',
#     build_by_default : true,
#     command          : [objcopy, '-O', 'binary', 'main.elf', 'main.bin'],
#     depends          : [main])

# mainhex = custom_target(
#                             'main.hex',
#         output           : ['main.hex'],
#         build_by_default : true,
#         command          : [objcopy, '-O', 'ihex', 'main.elf', 'main.hex'],
#         depends          : [main])

# mainsize = custom_target(
#                           'size',
#         capture          : true,
#         output           : ['main.size'],
#         build_by_default : true,
#         command          : [size, '--format=berkeley', 'main.elf'],
#         depends          : [main])

# if meson.get_compiler('c').get_id() == 'clang'
#     maindump = custom_target(
#                           'dump',
#         capture          : true,
#         output           : 'main.dump',
#         build_by_default : false,
#         command          : [objdump, '-triple=@0@-none-eabi'.format(arch), '-disassemble-all', '-S', '-t', 'main.elf'],
#         depends          : [main])

# elif meson.get_compiler('c').get_id() == 'gcc'
#   maindump = custom_target(
#                         'dump',
#       capture          : true,
#       output           : 'main.dump',
#       build_by_default : false,
#       command          : [objdump, '-D', '-S', '-t', 'main.elf'],
#       depends          : [main])
# endif
