#ifndef Value_h
#define Value_h

#include <string>

/**
 * @brief Value types
 */
enum class ValueType {
    NUMBER,
    OBJECT,
};

/**
 * @brief Object type.
*/
enum class ObjectType {
    STRING,
};

/**
 * @brief Base object
*/
struct Object {
    Object(ObjectType type) : type(type) {}
    ObjectType type;
};

/**
 * @brief String Object.
*/
struct StringObject : public Object {
    StringObject(const std::string &str) 
        : Object(ObjectType::STRING), string(str) {}
    std::string string;
};

/**
 * @brief Value (tagged union)
 */
struct Value {
    ValueType type;
    union {
        double number;
        Object* object;
    };
};

// ----------------------------
// Constructors

#define NUMBER(value) ((Value){ValueType::NUMBER, .number = value})

#define ALLOC_STRING(value) \
    ((Value){ValueType::OBJECT, .object = (Object*)new StringObject(value)})

// ----------------------------
// Accessors

#define AS_NUMBER(Value) ((double)(Value).number)
#define AS_OBJECT(Value) ((Object*)(Value).object)

#define AS_STRING(Value) ((StringObject*)(Value).object)
#define AS_CPPSTRING(Value) (AS_STRING(Value)->string)

// ----------------------------
// Testers

#define IS_NUMBER(Value) ((Value).type == ValueType::NUMBER)
#define IS_OBJECT(Value) ((Value).type == ValueType::OBJECT)

#define IS_OBJECT_TYPE(Value, ObjectType) \
    IS_OBJECT(Value) && (AS_OBJECT(Value)->type == ObjectType)

#define IS_STRING(Value) IS_OBJECT_TYPE(Value, ObjectType::STRING)

#endif