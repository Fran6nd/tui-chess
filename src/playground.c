#include "playground.h"
#include <ncurses.h>
#include <stdlib.h>
#include "piece.h"
#include "movement.h"

void plg_flip_map(plg_playground *plg)
{
    int x, y;
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 8; x++)
        {
            int y_bis = 7 - y;
            int tmp = plg->table[x][y];
            plg->table[x][y] = plg->table[x][y_bis];
            plg->table[x][y_bis] = tmp;
        }
    }
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 4; x++)
        {
            int x_bis = 7 - x;
            int tmp = plg->table[x][y];
            plg->table[x][y] = plg->table[x_bis][y];
            plg->table[x_bis][y] = tmp;
        }
    }
    plg->top_team = plg->top_team == TEAM_WHITE ? TEAM_BLACK : TEAM_WHITE;
}

plg_playground plg_new()
{
    plg_playground pl;
    pl.turn = TEAM_WHITE;
    pl.table[0][0] = WHITE_ROOK;
    pl.table[1][0] = WHITE_KNIGHT;
    pl.table[2][0] = WHITE_BISHOP;
    pl.table[3][0] = WHITE_QUEEN;
    pl.table[4][0] = WHITE_KING;
    pl.table[5][0] = WHITE_BISHOP;
    pl.table[6][0] = WHITE_KNIGHT;
    pl.table[7][0] = WHITE_ROOK;

    pl.table[0][1] = WHITE_PAWN;
    pl.table[1][1] = WHITE_PAWN;
    pl.table[2][1] = WHITE_PAWN;
    pl.table[3][1] = WHITE_PAWN;
    pl.table[4][1] = WHITE_PAWN;
    pl.table[5][1] = WHITE_PAWN;
    pl.table[6][1] = WHITE_PAWN;
    pl.table[7][1] = WHITE_PAWN;

    int x, y;
    for (x = 0; x < 8; x++)
    {
        for (y = 2; y < 6; y++)
        {
            pl.table[x][y] = EMPTY;
        }
    }
    pl.table[0][6] = BLACK_PAWN;
    pl.table[1][6] = BLACK_PAWN;
    pl.table[2][6] = BLACK_PAWN;
    pl.table[3][6] = BLACK_PAWN;
    pl.table[4][6] = BLACK_PAWN;
    pl.table[5][6] = BLACK_PAWN;
    pl.table[6][6] = BLACK_PAWN;
    pl.table[7][6] = BLACK_PAWN;

    pl.table[0][7] = BLACK_ROOK;
    pl.table[1][7] = BLACK_KNIGHT;
    pl.table[2][7] = BLACK_BISHOP;
    pl.table[3][7] = BLACK_QUEEN;
    pl.table[4][7] = BLACK_KING;
    pl.table[5][7] = BLACK_BISHOP;
    pl.table[6][7] = BLACK_KNIGHT;
    pl.table[7][7] = BLACK_ROOK;
    pl.possibilities.size = 0;

    pl.turn = TEAM_WHITE;
    pl.top_team = TEAM_WHITE;
    plg_flip_map(&pl);
    return pl;
}

static int plg_get_ennemy_team(int id)
{
    id = get_team(id);
    return id == TEAM_BLACK ? TEAM_WHITE : TEAM_BLACK;
}

/* return 0: no move, 1 move on emty, 2 move & eat. */
int positionition_is_valid(plg_playground *plg, int team, position target,
                           int mvt)
{
    if (target.x >= 0 && target.y >= 0 && target.x < 8 && target.y < 8)
    {
        switch (mvt)
        {
        case MVT_CAN_EAT:
            if (plg->table[target.x][target.y] == EMPTY)
            {
                return 1;
            }
            else if (team != get_team(plg->table[target.x][target.y]))
            {
                return 2;
            }

            break;
        case MVT_MUST_EAT:
            if ((team != get_team(plg->table[target.x][target.y])) &&
                (plg->table[target.x][target.y] != EMPTY))
            {
                return 2;
            }
            break;
        case MVT_CANT_EAT:
            if (plg->table[target.x][target.y] == EMPTY)
            {
                return 1;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

int plg_check_chess(plg_playground *plg)
{
    int x, y;
    for (x = 0; x < 8; x++)
    {
        for (y = 0; y < 8; y++)
        {
            possibilities_free(&plg->possibilities);
            possibilities_get(plg, 1);
            possibilities_free(&plg->possibilities);
        }
    }
    return 0;
}

/* RETURN -1 if cannot move because of chess, 0 if can't move, 1 if move on empty and 2 if move and eat. */
int positionsibilities_add(plg_playground *plg, possibilities *possibilities,
                           position from,
                           position delta, int mvt, int nested)
{
    if (plg->turn != plg->top_team)
    {
        delta.x = -delta.x;
        delta.y = -delta.y;
    }
    position p = {
        .x = delta.x + from.x,
        .y = delta.y + from.y,
    };
    int ret = positionition_is_valid(
        plg, get_team(plg->table[from.x][from.y]), p,
        mvt);
    if (ret == 0)
        return 0;
    /* There is a bug here somehow... */
    if (nested == 0)
    {
        plg_playground plg_tmp = *plg;
        plg_tmp.possibilities.size = 0;
        plg_move(&plg_tmp, from, p);
        possibilities_get(&plg_tmp, 1);
        int i;
        for (i = 0; i < plg_tmp.possibilities.size; i++)
        {
            position tmp = plg_tmp.possibilities.list[i]->pos_end;
            if ((plg_tmp.table[tmp.x][tmp.y] & (KING | plg_get_ennemy_team(plg_tmp.turn))) == (KING | plg_get_ennemy_team(plg_tmp.turn)))
            {
                possibilities_free(&plg_tmp.possibilities);
                return -1;
            }
        }
        possibilities_free(&plg_tmp.possibilities);
    }
    movement *mov = mov_new(plg, from, p, mvt);
    possibilities->size++;
    if (possibilities->size == 1)
    {
        possibilities->list = malloc(sizeof(movement *));
    }
    else
    {
        possibilities->list = (movement **)realloc(
            possibilities->list, possibilities->size * sizeof(movement *));
    }
    possibilities->list[possibilities->size - 1] = mov;
    return ret;
}

int possibilities_add_nocheck(plg_playground *plg, movement *mov)
{
    (&plg->possibilities)->size++;
    if ((&plg->possibilities)->size == 1)
    {
        (&plg->possibilities)->list = malloc(sizeof(movement *));
    }
    else
    {
        (&plg->possibilities)->list = (movement **)realloc(
            (&plg->possibilities)->list, (&plg->possibilities)->size * sizeof(movement *));
    }
    (&plg->possibilities)->list[(&plg->possibilities)->size - 1] = mov;
    return 1;
}

void positionsibilities_get_rook(plg_playground *plg, position from, int nested)
{
    int x = 0, y = 0;
    int i;
    for (i = x + 1; i < 8; i++)
    {
        if (positionsibilities_add(plg, &plg->possibilities, from, pos_new(x + i, y),
                                   MVT_CAN_EAT, nested) != 1)
        {
            break;
        }
    }
    for (i = x - 1; i > -8; i--)
    {
        if (positionsibilities_add(plg, &plg->possibilities, from, pos_new(x + i, y),
                                   MVT_CAN_EAT, nested) != 1)
        {
            break;
        }
    }
    for (i = y - 1; i > -8; i--)
    {
        if (positionsibilities_add(plg, &plg->possibilities, from, pos_new(x, y + i),
                                   MVT_CAN_EAT, nested) != 1)
        {
            break;
        }
    }
    for (i = y + 1; i < 8; i++)
    {
        if (positionsibilities_add(plg, &plg->possibilities, from, pos_new(x, y + i),
                                   MVT_CAN_EAT, nested) != 1)
        {
            break;
        }
    }
}

void positionsibilities_get_bishop(plg_playground *plg, position from, int nested)
{

    int x = 1, y = 1;
    for (y = 1; y < 8; y++)
    {
        int ret =
            positionsibilities_add(plg, &plg->possibilities, from, pos_new(x, y), MVT_CAN_EAT, nested);
        if (ret == 0 || ret == 2)
        {
            break;
        }
        x++;
    }
    x = 1;
    for (y = -1; y > -8; y--)
    {
        int ret =
            positionsibilities_add(plg, &plg->possibilities, from, pos_new(x, y), MVT_CAN_EAT, nested);
        if (ret == 0 || ret == 2)
        {
            break;
        }
        x++;
    }
    y = 1;
    for (x = -1; x > -8; x--)
    {
        int ret =
            positionsibilities_add(plg, &plg->possibilities, from, pos_new(x, y), MVT_CAN_EAT, nested);
        if (ret == 0 || ret == 2)
        {
            break;
        }
        y++;
    }
    y = -1;
    for (x = -1; x > -8; x--)
    {
        int ret =
            positionsibilities_add(plg, &plg->possibilities, from, pos_new(x, y), MVT_CAN_EAT, nested);
        if (ret == 0 || ret == 2)
        {
            break;
        }
        y--;
    }
}

void possibilities_get(plg_playground *plg, int nested)
{
    int x, y;
    for (x = 0; x < 8; x++)
    {
        for (y = 0; y < 8; y++)
        {
            if (get_team(plg->table[x][y]) == plg->turn)
            {
                position from = pos_new(x, y);
                {
                    switch (plg->table[x][y] & 0x0F0)
                    {
                    case PAWN:
                    {
                        int ret = positionsibilities_add(plg, &plg->possibilities, from, pos_new(0, 1), MVT_CANT_EAT, nested);
                        if ((ret == 1 || ret == -1) &&
                            has_moved(plg->table[x][y]) == 0)
                            positionsibilities_add(plg, &plg->possibilities, from, pos_new(0, 2), MVT_CANT_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(1, 1), MVT_MUST_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-1, 1), MVT_MUST_EAT, nested);
                    }
                    break;
                    case KNIGHT:
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-2, 1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-2, -1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(2, 1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(2, -1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(1, 2), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-1, 2), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(1, -2), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-1, -2), MVT_CAN_EAT, nested);
                        break;
                    case KING:
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-1, 1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-1, -1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(1, -1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(1, 1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(0, 1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(1, 0), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(0, -1), MVT_CAN_EAT, nested);
                        positionsibilities_add(plg, &plg->possibilities, from, pos_new(-1, 0), MVT_CAN_EAT, nested);
                        /* RocK */
                        if (!has_moved(plg->table[x][y]))
                        {
                            int x1;
                            if (plg->table[0][y] == (ROOK | plg->turn))
                            {
                                if (!has_moved(plg->table[0][y]))
                                {
                                    int empty = 1;
                                    for (x1 = 1; x1 < x; x1++)
                                    {
                                        if (plg->table[x1][y] != EMPTY)
                                        {
                                            empty = 0;
                                            break;
                                        }
                                    }
                                    if (empty)
                                    {
                                        movement *mov = mov_new_complicated(plg, pos_new(x, y), pos_new(x - 2, y), pos_new(0, y), pos_new(x - 1, y));
                                        possibilities_add_nocheck(plg, mov);
                                    }
                                }
                            }
                            if (plg->table[7][y] == (ROOK | plg->turn))
                            {
                                if (!has_moved(plg->table[7][y]))
                                {
                                    int empty = 1;
                                    for (x1 = x + 1; x1 < 7; x1++)
                                    {
                                        if (plg->table[x1][y] != EMPTY)
                                        {
                                            empty = 0;
                                            break;
                                        }
                                    }
                                    if (empty)
                                    {
                                        movement *mov = mov_new_complicated(plg, pos_new(x, y), pos_new(x + 2, y), pos_new(7, y), pos_new(x + 1, y));
                                        possibilities_add_nocheck(plg, mov);
                                    }
                                }
                            }
                        }
                        break;
                    case BISHOP:
                        positionsibilities_get_bishop(plg, from, nested);
                        break;
                    case ROOK:
                        positionsibilities_get_rook(plg, from, nested);
                        break;
                    case QUEEN:
                        positionsibilities_get_rook(plg, from, nested);
                        positionsibilities_get_bishop(plg, from, nested);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}
void possibilities_free(possibilities *possibilities)
{
    if (possibilities->size > 0)
    {
        int i;
        for (i = 0; i < possibilities->size; i++)
        {
            mov_free(possibilities->list[i]);
        }
        free(possibilities->list);
    }
    possibilities->size = 0;
}

void plg_move(plg_playground *plg, position from, position to)
{
    plg->table[to.x][to.y] = plg->table[from.x][from.y];
    plg->table[from.x][from.y] = EMPTY;
    if (to.y == ((plg->turn == TEAM_WHITE) ? 7 : 0) &&
        (plg->table[to.x][to.y] & PAWN) == PAWN)
    {
        plg->table[to.x][to.y] =
            ((plg->turn == TEAM_WHITE) ? WHITE_QUEEN : BLACK_QUEEN);
    }
    plg->table[to.x][to.y] |= HAS_MOVED;
    plg->turn = plg->turn == TEAM_BLACK ? TEAM_WHITE : TEAM_BLACK;
}