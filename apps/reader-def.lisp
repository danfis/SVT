(setq S '((45 Delim)
          (61 Delim)
          (43 Delim)

          (32 WhiteSpace)
          (10 WhiteSpace)
          (9 WhiteSpace)

          (112 Points0)
          (80 Points0)

          (101 Edges0)
          (69 Edges0)

          (102 Faces0)
          (70 Faces 0)
         )
(setq S2 '((105 Int1)
           (108 Long1)
           (115 String1)
           (102 Float1)
           (100 Double1)
           (99 Char1)))

(setq EndOfMsg nil)

(setq Type1 '((:num-non-zero Type3)
              (48 Type2))
)
(setq Type2 '((93 Type)))
(setq Type3 '((93 Type)
              (:num Type3)))
(setq Type nil)

(setq Char1 '((:anything Char)))
(setq Char nil)

(setq String1 '((34 String2)))
(setq String2 '((:str String2)
                (92 String3)
                (34 String)))
(setq String3 '((:anything String2)))
(setq String nil)

(setq Int1 '((45 Int2)
             (48 IntZero)
             (:num-non-zero Int)))
(setq Int2 '((:num-non-zero Int)))
(setq Int '((:num Int)))
(setq IntZero nil)
(setq Long1 '((45 Long2)
             (48 LongZero)
             (:num-non-zero Long)))
(setq Long2 '((:num-non-zero Long)))
(setq Long '((:num Long)))
(setq LongZero nil)


(setq Float1 '((45 Float2)
               (:num-non-zero Float3)
               (48 FloatZero)))
(setq Float2 '((:num-non-zero Float3)))
(setq Float3 '((:num Float3)
               (46 FloatDot1)))
(setq FloatZero '((46 FloatDot1)))
(setq FloatDot1 '((:num FloatDot)))
(setq FloatDot '((:num FloatDot)))
(setq Double1 '((45 Double2)
               (:num-non-zero Double3)
               (48 DoubleZero)))
(setq Double2 '((:num-non-zero Double3)))
(setq Double3 '((:num Double3)
               (46 DoubleDot1)))
(setq DoubleZero '((46 DoubleDot1)))
(setq DoubleDot1 '((:num DoubleDot)))
(setq DoubleDot '((:num DoubleDot)))



(setq states '(S S2 EndOfMsg Char1 Char String1 String2 String3 String
                Type1 Type2 Type3 Type
                Int1 Int2 Int IntZero Long1 Long2 Long LongZero
                Float1 Float2 Float3 FloatZero FloatDot1 FloatDot
                Double1 Double2 Double3 DoubleZero DoubleDot1 DoubleDot))
(setq end-states '(EndOfMsg
                   Type
                   Char
                   String
                   Int IntZero
                   Long LongZero
                   FloatZero Float3 FloatDot1 FloatDot FloatE
                   DoubleZero Double3 DoubleDot1 DoubleDot DoubleE
                   )
)

(load 'gen-lexer-tab.lisp)
(print-lex-c-table (lex-table states))
