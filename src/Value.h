#ifndef Value_h
#define Value_h

/**
 * @brief Value types
 */
enum class ValueType {
    NUMBER,
};

/**
 * @brief Value (tagged union)
 */
struct Value {
    ValueType type;
    union {
        double number;
    };
};

// ----------------------------
// Constructors

#define NUMBER(value) ((Value){ValueType::NUMBER, .number = value})

// ----------------------------
// Accessors

#define AS_NUMBER(Value) ((double)(Value).number)

#endif