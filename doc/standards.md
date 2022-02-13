# Coding standards

All of these are subject to change. Feel free to offer suggestions.

## Commenting

```
//Single-line comments

/* Doc string. Description of function.
 * @param arg1 Description
 * @param arg2 Description
 * @return Description
 */
```

## Naming

* Use camel-case, starting with lower-case, on everything but
  classes. Example `EntityManager* entityManager;`
* Use camel-case, starting with upper-case, on classes. Example
  `MessageBus`
* No need to prefix global variables with 'g' or 'g_'

## Classes

* Class members appended with an `_` underscore. Example `position_`
