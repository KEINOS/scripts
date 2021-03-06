<?php
/* ---------------------------------------------------------------------
    Main Function
   ------------------------------------------------------------------ */
/**
 * roll_dice function.
 *
 * Decode then curiculate dice code
 *
 * @access public
 * @param  string $dice_code
 * @return array
 */
function roll_dice($dice_code, $use_emoji = '')
{
    $dice_code     = (string) $dice_code;
    $is_emoji_mode = (isset($use_emoji) && $use_emoji == 'yes');

    $param      = explode('D', strtoupper(trim($dice_code)));
    $sum        = 0;
    $roll_num   = array();
    $roll_emoji = array();
    $times      = intval($param[0]);
    $max        = intval($param[1]);

    for ($i = 0; $i < $times; $i++) {
        $ii = rand(1, $max);
        $roll_num[]   = $ii;
        $roll_emoji[] = convert_num_to_emoji($ii);
        $sum += end($roll_num);
    }
    
    $roll = ($is_emoji_mode) ? $roll_emoji : $roll_num;

    $result = [
        'roll' => $roll,
        'sum'  => $sum,
    ];

    return $result;
}

/* ---------------------------------------------------------------------
    Getter Functions
   ------------------------------------------------------------------ */
function get_api_input_as_array()
{
    return json_decode(get_api_input_as_json(), JSON_OBJECT_AS_ARRAY);
}

function get_api_input_as_json()
{
    return urldecode(get_stdin_first_arg());
}

function get_stdin_first_arg()
{
    // CLIからの標準入力を取得
    global $argv;

    // 引数１は必須
    if (empty($argv[1])) {
        print_r($argv);
        die("Argument is empty.");
    }

    return trim($argv[1]);
}

/* ---------------------------------------------------------------------
    Miscellaneous Functions
   ------------------------------------------------------------------ */

/**
 * Set language to Japanese UTF-8 and Time zone to Japan
 */
function set_utf8_ja($timezone = 'Asia/Tokyo')
{
    if (! function_exists('mb_language')) {
        die('This application requires mb_language.');
    }

    date_default_timezone_set($timezone);
    setlocale(LC_ALL, 'ja_JP');
    mb_language('ja');
    mb_internal_encoding('UTF-8');
    mb_http_output('UTF-8');
    ob_start("mb_output_handler");
}


/**
 * convert_num_to_emoji function.
 *
 * サイコロの数字を emoji に変換して返す
 *
 * @access public
 * @param  mixed  $str
 * @return void
 */
function convert_num_to_emoji($str)
{
    $str = (string) $str;
    $map = [
        '0' => ':zero:',
        '1' => ':one:',
        '2' => ':two:',
        '3' => ':three:',
        '4' => ':four:',
        '5' => ':five:',
        '6' => ':six:',
        '7' => ':seven:',
        '8' => ':eight:',
        '9' => ':nine:',
    ];
    return strtr($str, $map);
}
