Coding Style Guideline
==========

Definition
==========
* camelCase: naming with camelCase starting with lowerCase character. Example: utils.h, buttonSize
* CamelCase: naming with camelCase starting with lowerCase character. Example: Scene.cpp, GameObject.h, FileDb
* Abbreviation rules: for abbreviation, the letters are NOT captalized. Example: playerId, cpuUsage, getUrl()
	Unless otherwise specified, abbreviation applies to camelCase and CamelCase.
* BLOCK_UNDERSCORE: naming with ALL_CAPITAL_LETTER, SEPERATED_BY_UNDERSCORE. Example: POPULATION_LIMIT, EACH_GAME_OBJECT
* lowercase: naming with all lower case, notseperatedbywhitespace. Example: gameobjects, scenes
	

File Naming Convention
==========

* All directories are named in lowercase.
* Files that defines/implements a class are named as CamelCase
* Files that does not defines/implements a class are named as camelCase
* Files of definition of platform-specific files shall have a _Implementation suffix.
This rules applies to all rules above.
Example: scene_Winapi.cpp


Identifier Naming Convention
==========
* All classes are named as CamelCase
* ^Except platform-specific classes, they are named with CamelCase_Implementation. Example: SceneRunner_Winapi
* All variables, functions and method are named as camalCase
* All constant and macro are named as BLOCK_UNDERSCORE


Coding Convention
==========

* Use tab indentation.
* Explicitly use `this->` to access class field and method. Example: `this->memberField` and `this->method()`
* Use inline brace:

@code
	if(condition){
		thereAre = manyLine();
		ofCode(HERE);
	}
@endcode

* Braces may be ignored for single statement:

@code
	if(condition)
		this->is = only(one, statement);
@endcode

* Do **not** document obvious code. It's counter-construtive. Do **not** document something like this:

@code
	///@brief get the value field of this class.
	int getValue() const{
		return this->value;
	}
@endcode

* Use doxygen for documentation. Details: http://www.stack.nl/~dimitri/doxygen/ ; Example:

@code
	/**	@brief	Link this object to b.
				When the attribute of b is updated,
				the attribute of this object is set to that of b.
				If bidirectional is true, the attribute of this object is also updated when b is updated.
		@param	The object to be linked
		@parem	If true, the update of attribute is bidirectional
		@return	this object.
	*/
	Object& link(Object& b, bool bidirectional=false){
		this->connection = b;
		if(bidirectional)
			b->link(*this);
		return *this;
	}
@endcode

