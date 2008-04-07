                    

(defun get-value (l key)
    " Returns value from list l according to given key or NIL if this key
      is not present in list.
      This function respects special symbols such as :num :num-non-zero etc... "
    (check-type key number)
    (check-type l list)

    (cond 
        ((null l) nil)
        ((equal key (caar l)) (cadar l))
        ((and (eq :num (caar l)) (>= key 48) (<= key 57)) (cadar l))
        ((and (eq :num-non-zero (caar l)) (>= key 49) (<= key 57)) (cadar l))
        ((and (not (equal key 92)) (not (equal key 34)) (eq :str (caar l))) (cadar l))
        ((eq :anything (caar l)) (cadar l))
        (t (get-value (cdr l) key))
    )
)

(defun default-list-helper (num symbol)
    (cond
        ((equal num 256) nil)
        (t (cons `(,num ,symbol) (default-list-helper (1+ num) symbol)))
    )
)
(defun default-list (symbol)
    " Returns list consisting by pairs (num symbol) where num goes from
      0 to 255 "
    (default-list-helper 0 symbol)
)

(defun is-in-list (l s)
    " Returns T if symbols S is in list L "
    (cond
        ((null l) nil)
        ((equal (car l) s) t)
        (t (is-in-list (cdr l) s))
    )
)

(defun choose-default (s)
    " Choose and return default symbol according to given symbol S.
      If S is in list of end-states returns 'S, otherwise it returns 'ERR "
    (if (is-in-list end-states s)
        'S
        'ERR)
)

(defun lex-line (state transitions)
    " This function returns one line of conversion table.
      The returned line belongs to given state and is constructed
      from given transitions "
    (let
        ((line (default-list (choose-default state)))) ; fill line by default values
        (mapcar #'(lambda (val)
                    " Replaces apropriate places in line by values from transitions table "
                    (let ((value (get-value transitions (car val))))
                        (if (not (null value))
                            `(,(car val) ,value)
                            val)
                    )
                  )
                line)
    )
)

(defun lex-table (states)
    " Returns constructed translation table "
    (mapcar #'(lambda (state)
                `(,state ,(lex-line state (eval state)))
              )
            states
    )
)

(defun print-c-enum (table)
    " Prints C enum of states "
    (format t "typedef enum {~%")
    (mapc #'(lambda (line)
                (format t "    ~A,~%" (car line))
            )
        table
    )
    (format t "    ERR,~%    NUM_STATES~%")
    (format t "} io_lexer_state_t;~%~%")
)


(defun print-table-line (line)
    (format t "    { ")
    (mapc
        #'(lambda (value)
            (format t "~A, " (cadr value))
          )
        (cadr line)
    )
    (format t "},~%")
)

(defun print-c-table (table)
    (format t "static io_lexer_state_t table[NUM_STATES][256] = {~%")
    (mapc ;; foreach line in table
        #'print-table-line 
        table
    )
    (print-table-line (list 'TMP (default-list 'ERR))) ;; last line for ERR state
    (format t "};~%")
)

(defun print-lex-c-table (table)
    "Print C table for lexer "
    (print-c-enum table)
    (print-c-table table)
)

;(print-lex-c-table (lex-table states))
;/* vim: set sw=4 ts=4 et ft=lisp ai tw=0: */
