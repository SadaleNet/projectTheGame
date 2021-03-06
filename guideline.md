Coding Style Guideline
==========

Definition
==========
* `camelCase`: naming with camelCase starting with `lowerCase` character. Example: `utils.h`, `buttonSize`
* `CamelCase`: naming with camelCase starting with `UpperCase` character. Example: `Scene.cpp`, `GameObject.h`, `FileDb`
* Abbreviation rules: for abbreviation, the subsequence letters are NOT captalized. Example: `playerId`, `cpuUsage`, `getUrl()`.
	Unless otherwise specified, abbreviation rules apply to `camelCase` and `CamelCase`.
* `BLOCK_UNDERSCORE`: naming with `ALL_CAPITAL_LETTER`, `SEPERATED_BY_UNDERSCORE`. Example: `POPULATION_LIMIT`, `EACH_GAME_OBJECT`
* `lowercase`: naming with all lower case, `notseperatedbywhitespace`. Example: `gameobjects`, `scenes`
	

File Naming Convention
==========

* All directories are named in `lowercase`.
* Files that defines/implements a class are named as `CamelCase`. Example: `Vec2.cpp`
* Files that does not defines/implements a class are named as `camelCase`. Example: `utils.h`
* Files of definition of platform-specific function/class/macro/whatever shall have a `_Implementation` suffix.
	This rules applies to all rules above. Example: `scene_Winapi.cpp`


Identifier Naming Convention
==========
* All classes are named as `CamelCase`
* ^Except platform-specific classes, they are named with `CamelCase_Implementation`. Example: `SceneRunner_Winapi`
* All variables, functions and method are named as `camalCase`
* All constants and macros are named as `BLOCK_UNDERSCORE`


Coding Convention
==========

* Use `tab` for indentation.
* Explicitly use `this->` to access class field and method. Example: `this->memberField` and `this->method()`
* Use inline brace:

```
	if(condition){
		thereAre = manyLine();
		ofCode(HERE);
	}
```

* Braces may be omitted for single statement:

```
	if(condition)
		this->is = only(one, statement);
```

* Do **not** document obvious code. It's counter-construtive. Do **not** document something like this:

```
	///@brief get the value field of this class.
	int getValue() const{
		return this->value;
	}
```

* Use doxygen for documentation. Details: http://www.stack.nl/~dimitri/doxygen/ ; Example:

```
	/**	@brief	Link this object to b.

				When the attribute of b is updated,
				the attribute of this object is set to that of b.
				If bidirectional is true, the attribute of this object is also updated when b is updated.
		@param	b	The object to be linked
		@param	bidirectional	If true, the update of attribute is bidirectional
		@return	this object.
	*/
	Object& link(Object& b, bool bidirectional=false){
		this->connection = b;
		if(bidirectional)
			b->link(*this);
		return *this;
	}
```

