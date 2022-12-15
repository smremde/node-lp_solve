declare module "lp_solve" {
    type ContraintTypes = "LE" | "EQ" | "GE";

    type SolveResult =
        "UNKNOWNERROR" |
        "DATAIGNORED" |
        "NOBFP" |
        "NOMEMORY" |
        "NOTRUN" |
        "OPTIMAL" |
        "SUBOPTIMAL" |
        "INFEASIBLE" |
        "UNBOUNDED" |
        "DEGENERATE" |
        "NUMFAILURE" |
        "USERABORT" |
        "TIMEOUT" |
        "RUNNING" |
        "PRESOLVED";

    class LinearProgram {
        constructor();

        addColumn(name?: string, isInteger?: boolean, isBinary?: boolean): string;
        setObjective(row: Row, minimize?: boolean): void;
        addConstraint(row: Row, constraint: ContraintTypes, constant: number, name?: string): void;
        dumpProgram(): string;
        solve(): Solution;

        /**
         * sets the amount of information to be reported by solve
         */
        setVerbose(verb: number): { verbosity: number; errorMsg?: string };

        getObjectiveValue(): number;
        getSolutionVariables(): number[] | null;
        get(variable: string): number | undefined | null;
        calculate(row: Row): number;

        Columns: { [index: string]: number };
        modelNames: boolean;
        localConstraints: boolean;
        lprec: LP;
    }

    interface LP {
        get_Nrows(): number;
        del_constraint(index: number): boolean;
    }

    /**
     * class to hold factor:attribute pairs
     */
    class Row {
        constructor(clone?: Row);

        /**
         * adds a row or a variable:factor to this row
         */
        Add(b: string, c?: number): Row;

        /**
         * subtract a row or variable:factor to this row
         */
        Subtract(b: string, c?: number): Row;

        /**
         * multiplies all the factors by a fixed value
         */
        Multiply(v: number): Row;

        /**
         * converts an object of vairable:factor to an equation for LP Solve
         */
        ToText(): string;

        raw: { [index: string]: number };
    }

    interface Solution {
        code: number;
        description: SolveResult;
    }
}