# Encrypted content

If you want to make it more difficult for other people to steal your code, you can put the content into a encrypted \*.zip file. Then define in the content settings the encryption parameters:

```json

```

## Password security

The password you provide is not the actual password of the \*.zip file. Open SilVerPLuM and click on the arrow next to 'Profile log'. There you can find the 'Encrypted content password generator'. Insert the password of the \*.zip file and put the output into the mod configuration.

Q: *"But SilVerPLuM is OpenSource. Everybody can just find out how the password is generated!"*

A: Everybody who has enough knowledge can decompile your modification from the resulting DLL. Somebody who has the skill to find the algorithm to break open the password can just decompile the DLL.
