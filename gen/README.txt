Options:
  -N            N
                (default 1e6)
  -T            T
                (default 1e6)
  -max_v        The maximum possible value of elements in sequence
                (default 1e9)
  -min_v        The minimum possible value of elements in sequence
                (default 0)
  -w<NUMBER>    <NUMBER> = 1, 2, 3
                The weight of the possibility performing operation <NUMBER>
                Too large weight will slow the speed of generator
                (default 1)
  -max_len      The maximum possible length of the sequence for all time
                Should be at least N
                (default 1e7)
  -min_len      The minimum possible length of the sequence for all time
                (default 0)
  -final_len    The exact length of the sequence after all operations
                If w3=0, use it carefully to avoid impossible assignment
                -1 means not specified
                (default -1)
  -n_ins_p      The number of positions that can be inserted
                The generator will randomly pick n_ins_p distinct numbers in [0, N]
                The generator will only insert new number at the positions if it can
                Too large (n_ins_p / N) slow the speed of generator
                -1 means not specified
                (default -1)
  -ins_p        The positions (ins_p and ins_p+1) that can be inserted
                If ins_p is greater than the length of the current sequence, 
                new elements will only be append at the end of the sequence
                If ins_p != -1, n_ins_p will be ignored.
                -1 means not specified
                (default -1)
  -del_p        The positions (del_p and del_p+1) that can be deleted
                If del_p is greater than the length of the current sequence, 
                The last element will be deleted
                -1 means not specified
                (default -1)
  -min_range    The minimum value of (r-l+1) in operation 3
                If the number of elements in sequence is less than min_range,
                it'll query the sum of entire sequence
                (default 1)
  -max_range    The maximum value of (r-l+1) in operation 3
                (default 1e7)
