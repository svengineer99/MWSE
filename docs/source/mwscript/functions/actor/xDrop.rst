
xDrop
========================================================

**Parameters:**

- ``string`` **objectID**: The object ID of the item to drop.
- ``long`` **count**: The number of items to drop.

**Returned:**

- *None*

This is a wrapper for the vanilla Drop function that can take variable input.

Note: when used on the player, both xDrop and Drop seem to leave a duplicate in the player's invenory, unless the item is equipped in which case it works as expected (no duplicate).  This note is based on limited testing; if you are using this function on the player, test thoroughly (and kidnly update this note with your findings.)
