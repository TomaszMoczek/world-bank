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
    data_frame = pandas.DataFrame(items)
    print("Projects per Region:")
    print()
    print(
        data_frame[["regionname", "lendprojectcost"]]
        .groupby("regionname", as_index=False)
        .count()
        .head(10)
    )
    print()
    print()
    print("Investments per Region:")
    print()
    print(
        data_frame[["regionname", "lendprojectcost"]]
        .groupby("regionname", as_index=False)
        .sum()
        .head(10)
    )


if __name__ == "__main__":
    main()
