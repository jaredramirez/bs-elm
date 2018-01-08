port module Main exposing (..)

import Html exposing (Html, div, button, text)
import Html.Events as Events
import Json.Encode as Encode
import Json.Decode as Decode


-- MODEL


type alias Model =
    { hello : String
    , todos : List Todo
    }


type alias Todo =
    { text : String
    , isComplete : Bool
    }


type alias Flags =
    { hello : String
    }


init : Flags -> ( Model, Cmd Msg )
init flags =
    { hello = flags.hello, todos = [] } ! []



-- MESSAGES


type Msg
    = CreateNewTodo



-- VIEW


view : Model -> Html Msg
view model =
    div []
        [ button [ Events.onClick CreateNewTodo ] [ text "press" ]
        , text "hello"
        ]



-- UPDATE


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        CreateNewTodo ->
            model
                ! [ sendInfoToReason <|
                        AddTodo
                            { text = "foo", isComplete = False }
                  ]



-- PORTS


todoEncoder : Todo -> Encode.Value
todoEncoder todo =
    Encode.object
        [ ( "text", Encode.string todo.text )
        , ( "isComplete", Encode.bool todo.isComplete )
        ]


type ReasonInfo
    = AddTodo Todo


sendInfoToReason : ReasonInfo -> Cmd msg
sendInfoToReason info =
    infoForReason <|
        case info of
            AddTodo todo ->
                { tag = "addTodo", payload = todoEncoder todo }


type alias Info =
    { tag : String
    , payload : Encode.Value
    }


port infoForReason : Info -> Cmd msg



-- SUBSCRIPTIONS


subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none



-- MAIN


main : Program Flags Model Msg
main =
    Html.programWithFlags
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        }
