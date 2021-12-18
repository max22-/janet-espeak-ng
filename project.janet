(declare-project :name "espeak-ng")
(declare-native
 :name "espeak-ng"
 :source @["espeak-ng.c"]
 :lflags [;default-lflags "-lespeak-ng"])
