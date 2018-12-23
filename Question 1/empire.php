<?php
class Empire
{
  public $case = 0;
  public $regionnum = 0;
  public $row = 0;
  public $column = 0;
  public $empire = [];
  public $regions = [];
  public $factions = [];
  public $contested = 0;
  public $visited = [];
  public $regionvisited = [];
  public $x = 0;
  public $y = 0;
  public $current_location = [];
  public $junction = [];
  public $pause_location = [];

  public function __construct($empire, $case)
  {
    $this->row = $empire['row'];
    $this->column = $empire['column'];
    $this->empire = $empire['empire'];
    $this->case = $case;

    $this->searchRegions();
    $this->searchFactions();
  }

  public function searchFactions() {
    foreach($this->regions as $key => $r) {
      $region = new Region($r);
      $faction = $region->getFactions();
      if($faction["type"] == "faction") {
        if(isset($this->factions[$faction["name"]]) && sizeof($this->factions[$faction["name"]]) > 0) {
        	$this->factions[$faction["name"]]++;
        } else {
        	$this->factions[$faction["name"]] = 1;
        }
      } else {
        $this->contested++;
      }
    }

    ksort($this->factions);

  }

  public function searchRegions() {
    for ($this->x = 0; $this->x < $this->row; $this->x++) {
      for($this->y = 0; $this->y < $this->column; $this->y++) {
        if ($this->checkVisited($this->x, $this->y)) {
          $this->updateDetail();
          if ($this->checkAlphabet($this->x, $this->y)) {
            $this->pause_location = [$this->x, $this->y];
            $this->updateRegionDetail();
            $direction = $this->checkSurrounding();
            while($direction) {
              if(sizeof($direction["direction"]) > 1) {
                array_push($this->junction, [$this->x, $this->y]);
              }

              $this->makeAMove($direction["direction"][0]);

              $direction = $this->checkSurrounding();
            }

            for($i = 0; $i < sizeof($this->junction); $i++) {
              $x = $this->junction[$i][0];
              $y = $this->junction[$i][1];
              $this->x = $x;
              $this->y = $y;
              $direction = $this->checkSurrounding();

              while($direction) {
                if(sizeof($direction["direction"]) > 1) {
                  array_push($this->junction, [$this->x, $this->y]);
                }

                $this->makeAMove($direction["direction"][0]);
                $direction = $this->checkSurrounding();
              }

              $this->removeJunction([[$x,$y]]);

            }

            $this->addVisited($this->regionvisited);
            $this->regionvisited = [];
            $this->junction = [];

            $this->x = $this->pause_location[0];
            $this->y = $this->pause_location[1];
            $this->regionnum++;
          }
        }
      }
    }
  }

  public function updateDetail() {
    $this->addVisited([[$this->x, $this->y]]);
    $this->current_location = [$this->x, $this->y];
  }

  public function updateRegionDetail() {
    $this->regions[$this->regionnum][] = [$this->empire[$this->x][$this->y]];
    $this->addRegionVisited([[$this->x, $this->y]]);
    $this->current_location = [$this->x, $this->y];
  }

  public function checkCharacter($x, $y) {
    return $this->empire[$x][$y] !== "#";
  }

  public function checkAlphabet($x, $y) {
    return ctype_alpha($this->empire[$x][$y]);
  }

  public function checkVisited($x, $y) {
    return !in_array([$x, $y], $this->visited);
  }

  public function checkRegionVisited($x, $y) {
    return !in_array([$x, $y], $this->regionvisited);
  }

  public function addVisited($node) {
    foreach($node as $n) {
      array_push($this->visited, $n);
    }
  }

  public function addRegionVisited($node) {
    foreach($node as $n) {
      array_push($this->regionvisited, $n);
    }
  }

  public function removeVisited($node) {
    foreach($node as $n) {
      $key = array_search($n, $this->visited);
      if ($key !== false) {
          unset($this->visited[$key]);
          $this->visited = array_values($this->visited);
      }
    }
  }

  public function removeRegionVisited($node) {
    foreach($node as $n) {
      $key = array_search($n, $this->regionvisited);
      if ($key !== false) {
          unset($this->regionvisited[$key]);
          $this->regionvisited = array_values($this->regionvisited);
      }
    }
  }

  public function removeJunction($node) {
    foreach($node as $n) {
      $key = array_search($n, $this->junction);
      if ($key !== false) {
          unset($this->junction[$key]);
          $this->junction = array_values($this->junction);
      }
    }
  }

  public function checkSurrounding() {
    $checkDirection = [
      "right" => $this->checkRight(),
      "down" => $this->checkDown(),
      "left" => $this->checkLeft(),
      "up" => $this->checkUp()
    ];

    $direction = [];

    foreach($checkDirection as $name => $d) {
      if ($d && $d["char"]) {
        if ($d['visited']) {
          $direction[] = $name;
        }
      }
    }
    if ($direction) {
      return [
        "type" => "move",
        "direction" => $direction
      ];
    } else {
      return false;
    }

  }

  public function checkUp() {
    if ($this->x > 0) {
      $visited = $this->checkRegionVisited($this->x - 1, $this->y);
      $char = $this->checkCharacter($this->x - 1, $this->y);
      return [
        "visited" => $visited,
        "char" => $char
      ];
    } else {
      return false;
    }
  }

  public function checkDown() {
    if ($this->x < $this->row - 1) {
      $visited = $this->checkRegionVisited($this->x + 1, $this->y);
      $char = $this->checkCharacter($this->x + 1, $this->y);
      return [
        "visited" => $visited,
        "char" => $char
      ];
    } else {
      return false;
    }
  }

  public function checkLeft() {
    if ($this->y > 0) {
      $visited = $this->checkRegionVisited($this->x, $this->y - 1);
      $char = $this->checkCharacter($this->x, $this->y - 1);
      return [
        "visited" => $visited,
        "char" => $char
      ];
    } else {
      return false;
    }
  }

  public function checkRight() {
    if ($this->y < $this->column - 1) {
      $visited = $this->checkRegionVisited($this->x, $this->y + 1);
      $char = $this->checkCharacter($this->x, $this->y + 1);
      return [
        "visited" => $visited,
        "char" => $char
      ];
    } else {
      return false;
    }
  }

  public function makeAMove($direction) {
    switch ($direction) {
      case 'up':
        $this->moveUp();
        break;

      case 'down':
        $this->moveDown();
        break;

      case 'left':
        $this->moveLeft();
        break;

      case 'right':
        $this->moveRight();
        break;

      default:
        break;
    }
    $this->updateRegionDetail();
  }

  public function moveUp() {
    $this->x = $this->x - 1;
  }

  public function moveDown() {
    $this->x = $this->x + 1;
  }

  public function moveLeft() {
    $this->y = $this->y - 1;
  }

  public function moveRight() {
    $this->y = $this->y + 1;
  }

  public function showResult() {

    echo "Case {$this->case}:<br>";
    foreach($this->factions as $name => $num) {
      echo "{$name} {$num}<br>";
    }
    echo "contested {$this->contested}<br>";
  }

}

class Region extends Empire
{
  public $region = [];

  public function __construct($arg)
  {
    $this->region = $arg;
  }

  public function getFactions() {
    $alpha = "";
    $num = 0;

    $contested = false;
    foreach($this->region as $r) {
      if(ctype_alpha($r[0])){
        if($alpha == "" || $r[0] == $alpha) {
          $alpha = $r[0];
        } else {
          return [
            "type" => "contested"
          ];
        }
      }
    }
    return [
      "type" => "faction",
      "name" => $alpha
    ];
  }
}
function initArray($prefix, $suffix, $input, $no = 0) {
  $arr = [];

  for($i = 0;$i < sizeof($input); $i++){
    $row = intval($input[$i]);
    $column = intval($input[$i+1]);
    $arr[$no]["row"] = $row;
    $arr[$no]["column"] = $column;
    $rowpos = $i + $prefix;

    for($k = 0;$k < $row;$k++) {
      $arr[$no]["empire"][] = str_split(trim($input[$rowpos + $k]));
    }

    $i = $i + $prefix - 1 + $suffix + $row;;

    $no++;
  }

  return $arr;
}

$myFile = "empire.txt";
$input = file($myFile);
$arr = initArray(2, 0, $input);

$no = 1;
foreach($arr as $v) {
  $empire = new Empire($v, $no);
  $empire->showResult();
  $no++;
}

?>
