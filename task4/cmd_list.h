DEF_CMD(PUSH, 1, {val = buf[++i]; push(&stk, val);})
DEF_CMD(POP, 2, {pop(&stk);})
DEF_CMD(ADD, 3, {push(&stk, pop(&stk) + pop(&stk));})
DEF_CMD(SUB, 4, {push(&stk, -(pop(&stk) - pop(&stk))) ;})
DEF_CMD(MUL, 5, {push(&stk, pop(&stk) * pop(&stk));})
DEF_CMD(DIV, 6, {push(&stk, (pop(&stk) / pop(&stk)));})
