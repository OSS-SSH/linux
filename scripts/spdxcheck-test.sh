#!/bin/sh

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# run check on a text and a binary file
for FILE in Makefile Documentation/logo.gif; do
	python3 scripts/spdxcheck.py $FILE
	python3 scripts/spdxcheck.py - < $FILE
<<<<<<< HEAD
done

# run check on complete tree to catch any other issues
python3 scripts/spdxcheck.py > /dev/null
=======
for PYTHON in python2 python3; do
	# run check on a text and a binary file
	for FILE in Makefile Documentation/logo.gif; do
		$PYTHON scripts/spdxcheck.py $FILE
		$PYTHON scripts/spdxcheck.py - < $FILE
	done

	# run check on complete tree to catch any other issues
	$PYTHON scripts/spdxcheck.py > /dev/null
done
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
done

# run check on complete tree to catch any other issues
python3 scripts/spdxcheck.py > /dev/null
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
