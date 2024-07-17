#!/usr/bin/python3
import os
import json
import pandas


def main() -> None:
    items: list[dict] = []
    file_path: str = os.path.join(
        os.path.dirname(os.path.abspath(__file__)), "world_bank.json"
    )
    with open(file_path, "r") as file:
        lines: list[str] = file.readlines()
    for line in lines:
        item: dict = json.loads(line.rstrip("\n"))
        items.append(item)
    data_frame: pandas.DataFrame = pandas.DataFrame(items)
    print(
        data_frame.loc[(data_frame["status"] == 'Active') | (data_frame["status"] == 'Closed'), ["regionname"]]
        .groupby(["regionname"], as_index=False)
        .size()
        .sort_values(["size"], ascending=False)
        .head(10)
        .to_string()
    )
    print()
    print(
        data_frame.loc[(data_frame["status"] == 'Active') | (data_frame["status"] == 'Closed'), ["regionname", "lendprojectcost"]]
        .groupby(["regionname"], as_index=False)
        .sum()
        .sort_values(["lendprojectcost"], ascending=False)
        .head(10)
        .to_string()
    )


if __name__ == "__main__":
    main()
