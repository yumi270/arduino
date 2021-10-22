<?php
/*3301058 田由美*/ 
				/*  -------------------------------------------------------
    			 *	Angle data api
				 *  -------------------------------------------------------
				 *  POST : save angle data
				 * 			roll , pitch , yaw
				 *  GET  : show current angle data
				 * 
				 */

				$currentDirectory = dirname(__FILE__);
    			// 角度データを保存するファイル
    			// ここでは一例としてPHPファイルと同一のディレクトリに配置します。
				$dataFile = $currentDirectory . "./angledata.dat" ;//目录

				//POST
				if($_SERVER["REQUEST_METHOD"] == "POST"){//请求方法
					// POSTリクエストが来た場合
    			    // 角度データをファイルに保存します。
					$angle=file_get_contents("php://input");//获得angle的数据  请求的原始数据的只读流 input输入
					file_put_contents("./angledata.dat",$angle);//数据放到angledata.dat文件里

				}else{
					//GET
					//	show current angle
					if(is_readable($dataFile)){
						//is_readable — ファイルが存在し、読み込み可能であるかどうかを知る
						// ファイルがある場合、ファイルの内容をechoします。
						$content=file_get_contents("./angledata.dat");//angledata.datの内容をget
						echo $content;//angledata.datの内容を出力
					}else{
						//	ファイルが存在しない場合の処理
						echo("data not found");
					}
				}
				echo header("refresh:0.5");//标题(在0.5秒内刷新)
				
				die();		//	 end of api
			?>
			
