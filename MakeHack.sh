# Paths
BASE_DIR=$(dirname "$(readlink -f "$0")")
TOOLS_DIR="c:/FE-Tools"
EA_DIR="$TOOLS_DIR/EventAssembler"


# EA main buildfile
main_event="$BASE_DIR/Main.event"


# ROMs
source_rom="$TOOLS_DIR/FE8U.gba"
target_rom="$BASE_DIR/HACK.gba"


# Tools
EA="$EA_DIR/ColorzCore.exe"


if [[ $1 == all ]]; then

	# Compile C
	cd "$BASE_DIR"
	echo "===== Compiling C ====="
	make clean
	make lyn
	echo "Compile CHAX .. done!"

fi

# if [[ $1 != quick ]]; then

	# # Assembling Tables
	# echo "===== Make C2EA ====="
	# cd "$BASE_DIR/GameData"
	# make clean
	# make tables
	# echo "Make Tables .. done!"

	# # Assembling Text
	# echo "===== Make Text ====="
	# cd "$BASE_DIR/Writans"
	# make clean
	# make
	# echo "Make Text .. done!"
	
	# # Make TMX
	# echo "===== Make Maps ====="
	# cd "$BASE_DIR/Chapters"
	# make clean
	# make maps
	# echo "Make TMX .. done!"
# fi


# Preparing ROM
cd "$BASE_DIR"
echo "===== Copy ROM ====="
cp -f "$source_rom" "$target_rom"
echo "Copy Target ROM .. done!"

# Make Hack
cd "$BASE_DIR"
echo "===== Make Hack ====="
"$EA" A FE8 "-input:$main_event" "-output:$target_rom"
echo "done!"
